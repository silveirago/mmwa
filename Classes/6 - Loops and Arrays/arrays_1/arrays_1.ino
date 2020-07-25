/* MAKING MUSIC WITH ARDUINO

  "Arrays"

  by Gustavo Silveira
  ofered by: www.musiconerd.com.br & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/

int note[7] = {36, 38, 40, 41, 43, 45, 47};
int octave[3] = {0, 12, 24};

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(115200);


}

void loop() {

  
    for (int i = 0; i < 7; i++) {
      MIDI.sendNoteOn(note[i] , 127, 1);
      delay(300);
      MIDI.sendNoteOn(note[i] , 0, 1);
    }
  


}
