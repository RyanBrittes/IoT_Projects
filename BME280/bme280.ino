#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_BME280 bme;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro ao inicializar o display OLED!");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (!bme.begin(0x76)) { // Troque para 0x77 se necessário
    Serial.println("BME280 não encontrado!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("BME280 N/A");
    display.display();
    while (1);
  }

  Serial.println("Sistema iniciado.");
}

void loop() {
  float temperatura = bme.readTemperature();
  float umidade = bme.readHumidity();
  float pressao = bme.readPressure() / 100.0;
  float altitude = bme.readAltitude(1013.25);

  // Exibe no Serial
  Serial.print("Temp: "); Serial.println(temperatura);
  Serial.print("Umid: "); Serial.println(umidade);
  Serial.print("Pressao: "); Serial.println(pressao);
  Serial.print("Alt: "); Serial.println(altitude);

  // Exibe no OLED
  display.clearDisplay();
  display.setCursor(0, 0);

  display.setTextSize(1);
  display.println("BME280 + OLED 0.96");

  display.setTextSize(1);
  display.print("Temp: ");
  display.print(temperatura);
  display.println(" C");

  display.print("Umid: ");
  display.print(umidade);
  display.println(" %");

  display.print("Press: ");
  display.print(pressao);
  display.println(" hPa");

  display.print("Alt: ");
  display.print(altitude);
  display.println(" m");

  display.display();
  delay(1500);
}