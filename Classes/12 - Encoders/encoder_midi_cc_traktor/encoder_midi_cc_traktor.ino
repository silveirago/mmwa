/* MAKING MUSIC WITH ARDUINO

  "Encoder 4 - MIDI CC for Traktor"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/

#include <EnableInterrupt.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define outputA 2
#define outputB 3

#define ledPin 5

int counter = 0;
int aState;
int aLastState;

/////////////////////////////////////////////
// buttons
const int NButtons = 1;
const int buttonPin[NButtons] = {4};     // the number of the pushbutton pin
int buttonCState[NButtons] = {0};         // stores the button current value
int buttonPState[NButtons] = {0};        // stores the button previous value

/////////////////////////////////////////////
// debounce
unsigned long lastDebounceTime[NButtons] = {0};  // the last time the output pin was toggled
unsigned long debounceDelay = 5;    // the debounce time; increase if the output flickers

/////////////////////////////////////////////
// midi
byte midiCh = 1; // MIDI channel to be used
byte note = 36; // Lowest MIDI note
byte cc = 1; // Lowest MIDI CC

void setup() {

  //  attachInterrupt(0, encoder, CHANGE);
  //  attachInterrupt(1, encoder, CHANGE);
  enableInterrupt(outputA, encoder, CHANGE);
  enableInterrupt(outputB, encoder, CHANGE);

  pinMode (outputA, INPUT_PULLUP);
  pinMode (outputB, INPUT_PULLUP);
  pinMode (buttonPin[0], INPUT_PULLUP);
  pinMode (ledPin, OUTPUT);

  Serial.begin (115200);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}

void loop() {

  buttons();

}

void encoder () {

  aState = digitalRead(outputA); // Reads the current "state" of the Encoder
  // If the previous state and the current state of outputA are different, it means that a pulse occurred
  if (aState != aLastState) {
    // If the outputB state is different from outputA it means that the Encoder is rotating clockwise
    if (digitalRead(outputB) != aState) {
      counter = 127; // Use this with traktor

      // Use this outside Traktor
      //      counter ++;
      //      if (counter > 127) {
      //        counter = 127;
      //      }
    } else {
      counter = 1; // Use this with Traktor

       // Use this outside Traktor
      //      counter --;
      //      if (counter < 0) {
      //        counter = 0;
      //      }
    }
    // Do what needs to be done

    //    // LED
    //    int ledCounter = map(counter, 0, 127, 0, 255); // Escales the counter to the pwm range 0-255
    //    analogWrite(ledPin, ledCounter);

    MIDI.sendControlChange(cc, counter, midiCh);

    //Serial.print("Midi CC: "); Serial.print(counter); Serial.print(" Led Brightness: ");Serial.println(ledCounter);

  }
  aLastState = aState; // Stores the actual value in the previous value

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


