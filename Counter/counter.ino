#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int HEIGHT = 64;
int WIDTH = 128;
int LED_PIN = 15;
int BUTTON = 2;
int count = -1;
bool previousState = HIGH;
bool LEDState = false;

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("FAILED!!"));

    for(;;);
  }

  display.clearDisplay();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.print("Contador: ");

  display.display();
}

void loop() {
  int pressButton = digitalRead(BUTTON);

  if (pressButton == LOW && previousState == HIGH) {
    LEDState = !LEDState;
    count++;
    digitalWrite(LED_PIN, LEDState);
    updateDisplay();
  }

  previousState = pressButton;
}

void updateDisplay(){
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Contador: ");

  display.setTextSize(1);
  display.setCursor(64, 20);
  display.print(count);

  display.display();
}