/* MAKING MUSIC WITH ARDUINO

  "MIDI in - velocity"

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

}

void handleNoteOn(byte channel, byte number, byte value) {

  switch (number) { //para usar a velocity para controlar o brilho, os leds precisam estar ligados em portas pwm
    case 36:
      analogWrite(ledPin[0], map(value, 0, 127, 0, 255)); // escalando o valor do midi 0-127 para o valor do analogWrite 0-255
      break;
    case 38:
      analogWrite(ledPin[1], map(value, 0, 127, 0, 255));
      break;
    case 42:
      analogWrite(ledPin[2], map(value, 0, 127, 0, 255));
      break;
    case 46:
      analogWrite(ledPin[3], map(value, 0, 127, 0, 255));
      break;
  }
}

void handleNoteOff(byte channel, byte number, byte value) {


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

