/* MAKING MUSIC WITH ARDUINO

  "Encoder 2 - Interrupts"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/

//#include <EnableInterrupt.h>

#define outputA 3
#define outputB 2

int counter = 0;
int aState;
int aLastState;

void setup() {

  attachInterrupt(0, encoder, CHANGE);
  attachInterrupt(1, encoder, CHANGE);
  
//  enableInterrupt(outputA, encoder, CHANGE);
//  enableInterrupt(outputB, encoder, CHANGE);
  
  pinMode (outputA, INPUT_PULLUP);
  pinMode (outputB, INPUT_PULLUP);

  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}

void loop() {

  

}

void encoder () {

  aState = digitalRead(outputA); // Reads the current "state" of the Encoder
  // If the previous state and the current state of outputA are different, it means that a pulse occurred
  if (aState != aLastState) {
    // If the outputB state is different from outputA it means that the Encoder is rotating clockwise
    if (digitalRead(outputB) != aState) {
      //counter ++;
      counter = 127;
      if (counter > 254) { // Limits to 127
        counter = 254;
      }
    } else {
      //counter --;
      counter = 0;
      if (counter < 0) { // Limits to 0
        counter = 0;
      }
    }

//int counterValue = map(counter, 0, 254, 0, 127);
//    Serial.println(counterValue);
Serial.println(counter);

  }
  aLastState = aState; // If the output_B state is different from OutputA it means that the Encoder is rotating clockwise...

}



