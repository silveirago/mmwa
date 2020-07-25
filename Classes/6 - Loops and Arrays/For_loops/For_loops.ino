/* MAKING MUSIC WITH ARDUINO

  "For Loops"

  by Gustavo Silveira
  ofered by: www.musiconerd.com.br & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/


#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(115200);

}

void loop() {

//  for (int counter = 0; counter < 12; counter++) {
//
//    MIDI.sendNoteOn(36 + counter, 127, 1);
//    delay(200);
//    MIDI.sendNoteOn(36 + counter, 0, 1);
//
//  }

  for (int counter = 0; counter < 12; counter++) {

    int note = random(20, 50);
    MIDI.sendNoteOn(note + counter, random(30, 127), 1);
    delay(random(50, 400));
    MIDI.sendNoteOn(note + counter, 0, 1);

  }



}
