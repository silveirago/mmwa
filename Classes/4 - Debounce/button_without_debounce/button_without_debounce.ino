int button = 2;
int led = 13;

int ledState = HIGH;
int buttonState;
int buttonPState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceTime = 50;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(button);

  if (buttonState != buttonPState) {
    if (buttonState == LOW) {

      ledState = !ledState;

      Serial.println(ledState);
    }
  }

  digitalWrite(led, ledState);

  buttonPState = buttonState;

}
