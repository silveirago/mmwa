/* MAKING MUSIC WITH ARDUINO

  "Encoder 3 - MIDI CC with LED"

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

void setup() {

  //  attachInterrupt(0, encoder, CHANGE);
  //  attachInterrupt(1, encoder, CHANGE);
  enableInterrupt(outputA, encoder, CHANGE);
  enableInterrupt(outputB, encoder, CHANGE);

  pinMode (outputA, INPUT_PULLUP);
  pinMode (outputB, INPUT_PULLUP);
  pinMode (ledPin, OUTPUT);

  Serial.begin (115200);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}

void loop() {

}

void encoder () {

  aState = digitalRead(outputA); // Reads the current "state" of the Encoder
  // If the previous state and the current state of outputA are different, it means that a pulse occurred
  if (aState != aLastState) {
    // If the outputB state is different from outputA it means that the Encoder is rotating clockwise
    if (digitalRead(outputB) != aState) {
      counter ++;
      if (counter > 127) {
        counter = 127;
      }
    } else {
      counter --;
      if (counter < 0) {
        counter = 0;
      }
    }
    // Do what needs to be done
    int ledCounter = map(counter, 0, 127, 0, 255); // Escales the counter to the pwm range 0-255
    
    //Serial.print("Midi CC: "); Serial.print(counter); Serial.print(" Led Brightness: ");Serial.println(ledCounter);
    analogWrite(ledPin, ledCounter);
    MIDI.sendControlChange(1, counter, 1);

  }
  aLastState = aState; // Stores the actual value in the previous value

}

