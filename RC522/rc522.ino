#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int PIN_RST = 4;
const int PIN_SDA = 5;
const int PIN_READ = 15;
const int PIN_REGISTER = 4;

MFRC522 leitor(PIN_SDA, PIN_RST);
const int maxCard = 10;
byte whiteList[maxCard][10];
int limitCards = 0;

String UID_TAG;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  leitor.PCD_Init();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("FAILED!!"));

    for(;;);
  }
  display.clearDisplay();

  pinMode(PIN_READ, INPUT_PULLUP);
  pinMode(PIN_REGISTER, INPUT_PULLUP);
}

void loop() {
  displayText();
  delay(50);
  
  bool readButton = digitalRead(PIN_READ);
  bool registerButton = digitalRead(PIN_REGISTER);
  
  if (readButton) {
    readCard();
  }

  if (registerButton) {
    registerCard();
  }
}

void displayText() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);

  display.print("Cadastro/Leitura");
  display.display();
}

void displayError() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.print("Erro na leitura!");

  display.display();
  delay(2000);
}

void displayRegister() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.println("Cartao registrado, ID: ");
  display.println(UID_TAG);

  display.display();
  delay(2000);
}

void displayRead() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.print("TAG: ");
  display.println(UID_TAG);

  display.display();
  delay(5000);
}

void displayOverflow() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.print("Memoria cheia!");

  display.display();
  delay(2000);
}

void displayRegistering() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);

  display.print("Registering");
  display.display();

  display.print(".");
  display.display();
  delay(500);

  display.print(".");
  display.display();
  delay(500);

  display.print(".");
  display.display();
  delay(500);
}

void displayReading() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);

  display.print("Reading");
  display.display();

  display.print(".");
  display.display();
  delay(500);

  display.print(".");
  display.display();
  delay(500);

  display.print(".");
  display.display();
  delay(500);
}

void readCard() {
  displayReading();
  if(leitor.PICC_IsNewCardPresent()){

    if(!leitor.PICC_ReadCardSerial()) {
      displayError();
    }

    else {

      for (byte i = 0; i < leitor.uid.size; i++) {
        if (leitor.uid.uidByte[i] < 0x10) {
          UID_TAG += " 0";
        } else {
          UID_TAG += " ";
        }
        UID_TAG += String(leitor.uid.uidByte[i], HEX);
      }

      Serial.print("UID: ");
      Serial.println(UID_TAG);

      displayRead();

      UID_TAG = "";

      leitor.PICC_HaltA();
    }
  }
}

void registerCard() {
  displayRegistering();

  if(leitor.PICC_IsNewCardPresent()){

    if(!leitor.PICC_ReadCardSerial()) {
      displayError();
    }

    else {

      if(limitCards <= maxCard){
        Serial.println("Memoria cheia!");
        displayOverflow();
        return;
      }

      for (int i = 0; i < limitCards; i++) {
        if (memcmp(whiteList[i], leitor.uid.uidByte, leitor.uid.size) == 0) {
          Serial.println("Cartão já cadastrado");
          return;
        }
      }

      memcmp(whiteList[limitCards], leitor.uid.uidByte, leitor.uid.size);
      limitCards++;

      Serial.println("Cartão cadastrado com sucesso!");
      displayRegister();

      leitor.PICC_HaltA();
      leitor.PCD_StopCrypto1();
    }
  }
}