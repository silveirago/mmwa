#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();


int potPin = A0;

int midiCState = 0; //estado atual do midi
int midiPState = 0; //estado previo do midi

int potCState = 0; //estado atual
int potPState = 0; //estado previo
int potVar = 0;

void setup () {

  Serial.begin(115200);

}

void loop () {

  potCState = analogRead(potPin);
  midiCState = map(potCState, 0, 1023, 0, 127);

  potVar = abs(potCState - potPState);


  if (potVar > 4) {
    if (midiPState != midiCState) {

      MIDI.sendControlChange(1, midiCState, 1);

//      Serial.print("Pot Value = ");
//      Serial.print(potCState);
//      Serial.print("    Midi Value = ");
//      Serial.print(midiCState);
//      Serial.print("\n");

      midiPState = midiCState;
      potPState = potCState;

    }
  }
}
