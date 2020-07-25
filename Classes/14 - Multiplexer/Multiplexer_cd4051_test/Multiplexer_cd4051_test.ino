#include "analogmuxdemux.h" // https://github.com/ajfisher/arduino-analog-multiplexer

//* Define s0, s1, s2, s3, and x pins
#define s0 2
#define s1 3
#define s2 4
#define x1 A1 // analog pin of the first mux

//Multiplexer4067 mplex = Multiplexer4067(s0, s1, s2, s3, x1);
AnalogMux mplex(s0, s1, s2, x1);
//AnalogMux amux(4,3,2, READPIN);

const int N_MUX_PINS = 8; // total number of components connected to the mux
int muxPin[N_MUX_PINS] = {0, 1, 2, 3, 4, 5, 6, 7}; // pins used int the mux


void setup() {

  Serial.begin(115200);

  pinMode(x1, INPUT_PULLUP);

}

void loop() {

  readMux();

  //  delay(50);
}

// Reads the mux pins and prints its values in the serial monitor
void readMux() {

  for (int i = 0; i < N_MUX_PINS; i++) {
    Serial.print(i);
    Serial.print(": ");
    //Serial.print(map(mplex.readChannel(i), 0, 1022, 0, 127));
    mplex.SelectPin(muxPin[i]); // choose the pin you want to send signal to off the DeMux
    Serial.print(mplex.AnalogRead());
    Serial.print("   ");
  }

  Serial.println();
  delay(10);

}
