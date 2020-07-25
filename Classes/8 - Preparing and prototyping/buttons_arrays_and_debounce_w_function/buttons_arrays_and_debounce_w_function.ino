/* MAKING MUSIC WITH ARDUINO

  "Buttons inside a function"

  by Gustavo Silveira
  ofered by: www.musiconerd.com.br & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/


#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

/////////////////////////////////////////////
// buttons
const int NButtons = 3;
const int buttonPin[NButtons] = {2,3,4};     // the number of the pushbutton pin
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

  Serial.begin(115200);

  for (int i = 0; i < NButtons; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

}

void loop() {

buttons();

}

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

