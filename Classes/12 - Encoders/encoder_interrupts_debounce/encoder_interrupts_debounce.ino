/* MAKING MUSIC WITH ARDUINO

  "Encoder 2 - Interrupts"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/
#include <Bounce2.h>
//#include <EnableInterrupt.h>

#define outputA 3
#define outputB 2

int counter = 0;
int aState;
int aLastState;

// Instantiate a Bounce object
Bounce debouncer1 = Bounce(); 
// Instantiate another Bounce object
Bounce debouncer2 = Bounce(); 

void setup() {

  attachInterrupt(0, encoder, CHANGE);
  attachInterrupt(1, encoder, CHANGE);

  //  enableInterrupt(outputA, encoder, CHANGE);
  //  enableInterrupt(outputB, encoder, CHANGE);

  debouncer1.attach(outputA);
  debouncer1.interval(1); // interval in ms
  debouncer2.attach(outputB);
  debouncer2.interval(1); // interval in ms

  pinMode (outputA, INPUT_PULLUP);
  pinMode (outputB, INPUT_PULLUP);

  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}

void loop() {
  debouncer1.update();
  debouncer2.update();


}

void encoder () {

  int readingA = debouncer1.read();
  int readingB = debouncer2.read();

  aState = readingA; // Reads the current "state" of the Encoder
  // If the previous state and the current state of outputA are different, it means that a pulse occurred
  if (aState != aLastState) {
    // If the outputB state is different from outputA it means that the Encoder is rotating clockwise
    if (readingB != aState) {
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



