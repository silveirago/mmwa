#include "Multiplexer4067.h"


Multiplexer4067 mplex = Multiplexer4067(2, 3, 4, 5, A0);


void setup() {

  Serial.begin(9600);
  mplex.begin();
  
  //mplex.readChannel(0);//it read the channel 0
  
  //default it read 5 times but can be changed:
  //mplex.readChannel(0,10);
}

void loop() {

  //  Serial.println(mplex.readChannel(0));
  //  delay(50);

  readAll();

}

void readAll() {

  for (int i = 0; i < 4; i++) {
    Serial.print(i);
    Serial.print(": ");
    //Serial.print(map(mplex.readChannel(i), 0, 1022, 0, 127));
    Serial.print(mplex.readChannel(i));
    Serial.print("   ");
  }
  
  Serial.println();
  delay(10);

}
