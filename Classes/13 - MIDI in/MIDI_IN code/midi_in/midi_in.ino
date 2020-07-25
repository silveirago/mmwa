/* MAKING MUSIC WITH ARDUINO

  "MIDI in"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();


void setup() {

  MIDI.begin();
  Serial.begin(115200);

  MIDI.setHandleControlChange(handleControlChange); // Listens to control change
  MIDI.setHandleNoteOn(handleNoteOn); // Listens to note ons
  MIDI.setHandleNoteOff(handleNoteOff); // Listens to note offs

}

void loop() {

  MIDI.read(); // The only thing that should be in the loop for "MIDI in"

}

////////////////////////////////////////////
// MIDI IN
void handleControlChange(byte channel, byte number, byte value) { // channel, CC, value

}


void handleNoteOn(byte channel, byte number, byte value) { // channel, note, velocity


}


void handleNoteOff(byte channel, byte number, byte value) { // channel, note, velocity


}

