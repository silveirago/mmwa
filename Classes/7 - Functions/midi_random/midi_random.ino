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
    sendMidi(24, 36, 100);
  }
  if (buttonState[1] == LOW) {
    sendMidi(40, 80, 1000);
  }
  if (buttonState[2] == LOW) {
    sendMidi(24, 120, 500);
  }

}

void sendMidi(int a, int b, int c) {

  int randomNote = random(a, b);

  MIDI.sendNoteOn(randomNote, 127, 1);
  delay(c);
  MIDI.sendNoteOn(randomNote, 0, 1);

}





