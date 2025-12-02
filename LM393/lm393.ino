#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int valueAnalogic = 0;

void setup() {
  Serial.begin(115200);
  pinMode(15, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro ao inicializar o display OLED!");
    while (1);
  }
  display.clearDisplay();

}

void loop() {
  bool valueDigital = digitalRead(15);
  valueAnalogic = analogRead(34);

  Serial.println(valueDigital);
  Serial.println(valueAnalogic);

  displayUpdate();

  delay(500);
}

void displayUpdate(){
  display.clearDisplay();

  display.drawLine(0, 0, 0, 63, WHITE);
  display.drawLine(0, 0, 123, 0, WHITE);
  display.drawLine(0, 63, 123, 63, WHITE);
  display.drawLine(123, 0, 123, 63, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);

  display.print("Humidade: ");
  display.print(((-valueAnalogic * 100) / 4095) + 100);
  display.print(" %");

  display.display();
}