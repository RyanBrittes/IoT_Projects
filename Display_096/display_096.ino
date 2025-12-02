#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("FAILED!!"));

    for(;;);
  }

  display.clearDisplay();

  display.drawLine(0, 0, 0, 63, WHITE);
  display.drawLine(127, 0, 127, 63, WHITE);
  display.drawLine(0, 0, 127, 0, WHITE);
  display.drawLine(0, 63, 128, 63, WHITE);

  display.display();

  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  circle();
  delay(1000);
  triangle();
  delay(1000);
  rectangle();
  delay(1000);
}

void circle() {
  display.clearDisplay();

  digitalWrite(15, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);

  display.drawLine(0, 0, 0, 63, WHITE);
  display.drawLine(127, 0, 127, 63, WHITE);
  display.drawLine(0, 0, 127, 0, WHITE);
  display.drawLine(0, 63, 128, 63, WHITE);

  display.drawCircle(63, 31, 20, WHITE);

  display.display();
}

void triangle() {
  display.clearDisplay();

  digitalWrite(15, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);

  display.drawLine(0, 0, 0, 63, WHITE);
  display.drawLine(127, 0, 127, 63, WHITE);
  display.drawLine(0, 0, 127, 0, WHITE);
  display.drawLine(0, 63, 128, 63, WHITE);

  display.drawTriangle(63, 11, 48, 41, 78, 41, WHITE);

  display.display();
}

void rectangle() {
  display.clearDisplay();

  digitalWrite(15, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);

  display.drawLine(0, 0, 0, 63, WHITE);
  display.drawLine(127, 0, 127, 63, WHITE);
  display.drawLine(0, 0, 127, 0, WHITE);
  display.drawLine(0, 63, 128, 63, WHITE);

  display.drawRect(23, 11, 80, 40, WHITE);

  display.display();
}