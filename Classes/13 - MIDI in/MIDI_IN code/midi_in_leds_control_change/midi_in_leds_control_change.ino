/* MAKING MUSIC WITH ARDUINO

  "MIDI in - control change"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

const int NLed = {4};
int ledPin[NLed] = {3, 5, 6, 9};

void setup() {

  for (int i = 0; i < NLed; i++) {
    pinMode(ledPin[i], OUTPUT);
  }

  MIDI.begin();
  Serial.begin(115200);

  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

}

void loop() {

  MIDI.read();

}

void handleControlChange(byte channel, byte number, byte value) {

  switch (number) {
    case 1:
      analogWrite(ledPin[0], map(value, 0, 127, 0, 255));
      break;
    case 2:
      analogWrite(ledPin[1], map(value, 0, 127, 0, 255));
      break;
    case 3:
      analogWrite(ledPin[2], map(value, 0, 127, 0, 255));
      break;
    case 4:
      analogWrite(ledPin[3], map(value, 0, 127, 0, 255));
      break;
  }
}

void handleNoteOn(byte channel, byte number, byte value) {


}

void handleNoteOff(byte channel, byte number, byte value) {



}

