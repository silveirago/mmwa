/* MAKING MUSIC WITH ARDUINO

  "Sending Midi CC"

  by Gustavo Silveira
  ofered by: www.musiconerd.com.br & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/


#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int potPin = A0; // Pin where the potentiometer is

int potCState = 0; // Current state of the pot
int potPState = 0; // Previous state of the pot
int potVar = 0; // Difference between the current and previous state of the pot

int midiCState = 0; // Current state of the midi value
int midiPState = 0; // Previous state of the midi value

int TIMEOUT = 300; // Amount of time the potentiometer will be read after it exceeds the varThreshold
int varThreshold = 6; // Threshold for the potentiometer signal variation
boolean potMoving = true; // If the potentiometer is moving
int PTime = 0; // Previously stored time
int timer = 0; // Stores the time that has elapsed since the timer was reset

void setup () {

  Serial.begin(115200); // Hairlles midi's baud rate (115200);

}

void loop () {

  potCState = analogRead(potPin); // Reads the pot and stores it in the potCState variable
  midiCState = map(potCState, 0, 1023, 0, 127); // Maps the reading of the potCState to a value usable in midi


  potVar = abs(potCState - potPState); // Calculates the absolute value between the difference between the current and previous state of the pot

  if (potVar > varThreshold) { // Opens the gate if the potentiometer variation is greater than the threshold
    PTime = millis(); // Stores the previous time
  }

  timer = millis() - PTime; // Resets the timer 
  if (timer < TIMEOUT) { // If the timer is less than the maximum allowed time it means that the potentiometer is still moving
    potMoving = true;
  }
  else {
    potMoving = false;
  }

  if (potMoving == true) { // If the potentiometer is still moving, send the change control
    if (midiPState != midiCState) {
      //Serial.println(midiCState);
      MIDI.sendControlChange(1, midiCState, 1);
      potPState = potCState; // Stores the current reading of the potentiometer to compare with the next
      midiPState = midiCState;
    }
  }

}

