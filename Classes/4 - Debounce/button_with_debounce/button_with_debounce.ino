int button = 2;
int led = 13;

int ledState = HIGH;
int buttonState;
int buttonPState = HIGH;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 20;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, ledState);
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(button);

  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (buttonState != buttonPState) {     
      lastDebounceTime = millis();

      if (buttonState == LOW) {
        ledState = !ledState;
        Serial.println(ledState);
      }
      buttonPState = buttonState;
    }
  }

  

  digitalWrite(led, ledState);

}
