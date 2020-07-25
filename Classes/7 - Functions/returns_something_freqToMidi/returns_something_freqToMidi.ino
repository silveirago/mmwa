#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int buttonPin[3] = {2, 3, 4};
int buttonState[3] {0};

int ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

// the loop function runs over and over again forever
void loop() {

  for (int i = 0; i < 3; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
  }

  if (buttonState[0] == LOW) {
    MIDI.sendNoteOn(freqToMidi(200), 127, 1);
    delay(500);
    MIDI.sendNoteOn(freqToMidi(200), 0, 1);
  }

  if (buttonState[1] == LOW) {
    MIDI.sendNoteOn(freqToMidi(400), 127, 1);
    delay(500);
    MIDI.sendNoteOn(freqToMidi(400), 0, 1);
  }

  if (buttonState[2] == LOW) {
    MIDI.sendNoteOn(freqToMidi(800), 127, 1);
    delay(500);
    MIDI.sendNoteOn(freqToMidi(800), 0, 1);
  }

}

int freqToMidi(float f)
{
  int midival = log(f / 440.0) / log(2) * 12 + 69;
  return midival;
}




