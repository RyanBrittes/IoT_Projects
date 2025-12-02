int LED_PIN = 15;
int BUTTON = 2;
bool previousState = HIGH;
bool LEDState = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {
  int pressButton = digitalRead(BUTTON);

  if (pressButton == LOW && previousState == HIGH) {
    LEDState = !LEDState;
    digitalWrite(LED_PIN, LEDState);
  }

  previousState = pressButton;
}
