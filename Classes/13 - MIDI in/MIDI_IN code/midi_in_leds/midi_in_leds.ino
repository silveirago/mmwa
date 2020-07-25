/* MAKING MUSIC WITH ARDUINO

  "MIDI in - note on/off"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

const int NLed = 4; // Number of leds
int ledPin[NLed] = {3, 5, 6, 9}; // Led pins

void setup() {

  for (int i = 0; i < NLed; i++) {
    pinMode(ledPin[i], OUTPUT);
  }

  MIDI.begin();
  Serial.begin(115200);

  MIDI.setHandleControlChange(handleControlChange); // Listens to control change
  MIDI.setHandleNoteOn(handleNoteOn); // Listens to note ons
  MIDI.setHandleNoteOff(handleNoteOff); // Listens to note offs

}

void loop() {

  MIDI.read(); // The only thing that should be in the loop for "MIDI in"

}

void handleControlChange(byte channel, byte number, byte value) { // channel, CC, value

}

void handleNoteOn(byte channel, byte number, byte value) { v
  
  switch (number) {
    case 36: // if (number == 36) { digitalWrite(ledPin[0], HIGH); }
      digitalWrite(ledPin[0], HIGH);
      break;
    case 38:
      digitalWrite(ledPin[1], HIGH);
      break;
    case 42:
      digitalWrite(ledPin[2], HIGH);
      break;
    case 46:
      digitalWrite(ledPin[3], HIGH);
      break;
  }
  
}

void handleNoteOff(byte channel, byte number, byte value) { // channel, note, velocity
    
    switch (number) {
    case 36:
      digitalWrite(ledPin[0], LOW);
      break;
    case 38:
      digitalWrite(ledPin[1], LOW);
      break;
    case 42:
      digitalWrite(ledPin[2], LOW);
      break;
    case 46:
      digitalWrite(ledPin[3], LOW);
      break;
  }
}

