#define LED_PIN 2

void setup() {
  // Inicializando o pino do LED como saída
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Acendendo o LED
  digitalWrite(LED_PIN, HIGH);
  // Esperando 0,5 segundos
  delay(500);
  // Desligando o LED
  digitalWrite(LED_PIN, LOW);
  // Esperando mais 0,5 segundos
  delay(500);
}