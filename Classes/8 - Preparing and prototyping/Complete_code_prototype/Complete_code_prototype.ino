#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();

/////////////////////////////////////////////
// buttons
const int NButtons = 12; //*
const int buttonPin[NButtons] = {10, 16, 14, 15, 6, 7, 8, 9, 2, 3, 4, 5};     //* the number of the pushbutton pin
int buttonCState[NButtons] = {0};         // stores the button current value
int buttonPState[NButtons] = {0};        // stores the button previous value

/////////////////////////////////////////////
// debounce
unsigned long lastDebounceTime[NButtons] = {0};  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    //* the debounce time; increase if the output flickers

/////////////////////////////////////////////
// potentiometers

const int NPots = 4; //*
int potPin[NPots] = {A3, A2, A1, A0}; //* Pin where the potentiometer is
int potCState[NPots] = {0}; // Current state of the pot
int potPState[NPots] = {0}; // Previous state of the pot
int potVar = 0; // Difference between the current and previous state of the pot

int midiCState[NPots] = {0}; // Current state of the midi value
int midiPState[NPots] = {0}; // Previous state of the midi value

int TIMEOUT = 300; //* Amount of time the potentiometer will be read after it exceeds the varThreshold
int varThreshold = 10; //* Threshold for the potentiometer signal variation
boolean potMoving = true; // If the potentiometer is moving
unsigned long PTime[NPots] = {0}; // Previously stored time
unsigned long timer[NPots] = {0}; // Stores the time that has elapsed since the timer was reset

/////////////////////////////////////////////

byte midiCh = 1; //* MIDI channel to be used
byte note = 36; //* Lowest note to be used
byte cc = 1; //* Lowest MIDI CC to be used

void setup() {

  Serial.begin(115200);

    for (int i = 0; i < NButtons; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

}

void loop() {

buttons();
potentiometers();

}

/////////////////////////////////////////////
// BUTTONS
void buttons() {

    for (int i = 0; i < NButtons; i++) {

    buttonCState[i] = digitalRead(buttonPin[i]);

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {

      if (buttonPState[i] != buttonCState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonCState[i] == LOW) {
          MIDI.sendNoteOn(note + i, 127, midiCh);
          //          Serial.print("button on  >> ");
          //          Serial.println(i);
        }
        else {
          MIDI.sendNoteOn(note + i, 0, midiCh);
          //          Serial.print("button off >> ");
          //          Serial.println(i);
        }
        buttonPState[i] = buttonCState[i];
      }
    }
  }
}

/////////////////////////////////////////////
// POTENTIOMETERS
void potentiometers() {
  
    for (int i = 0; i < NPots; i++) { // Loops through all the potentiometers
    
    potCState[i] = analogRead(potPin[i]); // Reads the pot and stores it in the potCState variable
    midiCState[i] = map(potCState[i], 0, 1023, 0, 127); // Maps the reading of the potCState to a value usable in midi


    potVar = abs(potCState[i] - potPState[i]); // Calculates the absolute value between the difference between the current and previous state of the pot

    if (potVar > varThreshold) { // Opens the gate if the potentiometer variation is greater than the threshold
      PTime[i] = millis(); // Stores the previous time
    }

    timer[i] = millis() - PTime[i]; // Resets the timer 11000 - 11000 = 0ms

    if (timer[i] < TIMEOUT) { // If the timer is less than the maximum allowed time it means that the potentiometer is still moving
      potMoving = true;
    }
    else {
      potMoving = false;
    }

    if (potMoving == true) { // If the potentiometer is still moving, send the change control
      if (midiPState[i] != midiCState[i]) {
        //Serial.println(midiCState);
        MIDI.sendControlChange(cc+i, midiCState[i], midiCh);
        potPState[i] = potCState[i]; // Stores the current reading of the potentiometer to compare with the next
        midiPState[i] = midiCState[i];
      }
    }
  }
  
}
