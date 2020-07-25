/* MAKING MUSIC WITH ARDUINO

  "Encoder 1"

  by Gustavo Silveira
  ofered by: www.musiconerd.com & www.bitcontrollers.com
  gustavosilveira@musiconerd.com

*/
 
 #define outputA 2 // Pin A
 #define outputB 3 // Pin B

 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (outputA,INPUT_PULLUP);
   pinMode (outputB,INPUT_PULLUP);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);  //previous state
 } 

 void loop() { 
   aState = digitalRead(outputA); // Reads the current "state" of the Encoder
   // If the previous state and the current state of outputA are different, it means that a pulse occurred
   if (aState != aLastState){     
     // If the outputB state is different from outputA it means that the Encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++; // counter = counter + 1
     } else {
       counter --; // counter = counter - 1
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // If the output_B state is different from OutputA it means that the Encoder is rotating clockwise...
 }
