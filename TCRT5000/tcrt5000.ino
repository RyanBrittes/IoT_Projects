#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int OUT_A0 = 32;
int OUT_D0 = 34;
int LED = 15;
int stateA0 = 0;
String stateWindow = "Aberto";

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("FAILED!!"));

    for(;;);
  }

  display.clearDisplay();

  pinMode(OUT_A0, INPUT);
  pinMode(OUT_D0, INPUT);
  pinMode(LED, OUTPUT);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println(stateWindow);

  display.display();

}

void loop() {
  bool stateD0 = digitalRead(OUT_D0);
  stateA0 = analogRead(OUT_A0);

  updateDisplay();

  if (stateA0 < 2040){
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }

  if (stateSensor == false){
    digitalWrite(LED, HIGH);
    stateWindow = "Fechado";
    updateDisplay();
  }
  else {
    digitalWrite(LED, LOW);
    stateWindow = "Aberto";
    updateDisplay();
  }

  delay(50);
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.print(stateA0);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 40);
  display.print(stateWindow);

  display.display();
}