#include <LiquidCrystal.h>

// LCD ligado nos pinos 2,3,4,5,6,7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Sensores e atuadores
const int pinLDR      = A0;
const int pinVerde    = 8;
const int pinAmarelo  = 9;
const int pinVermelho = 10;
const int pinBuzzer   = 11;

int estadoAnterior = -1;

void setup() {

  pinMode(pinVerde, OUTPUT);
  pinMode(pinAmarelo, OUTPUT);
  pinMode(pinVermelho, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  Serial.begin(9600);

  // Inicia LCD
  lcd.begin(16, 2);

  // Mensagem inicial
  lcd.setCursor(0, 0);
  lcd.print("Eng. Software");

  lcd.setCursor(0, 1);
  lcd.print("Monitor Luz");

  delay(2000);

  lcd.clear();
}

void loop() {

  // Leitura do LDR
  int leitura = analogRead(pinLDR);

  Serial.println(leitura);

  // Estados
  int estado;

  if (leitura > 850) {
    estado = 0; // BOM
  }
  else if (leitura >= 400) {
    estado = 1; // MEDIA
  }
  else {
    estado = 2; // RUIM
  }

  // LEDs
  digitalWrite(pinVerde, estado == 0);
  digitalWrite(pinAmarelo, estado == 1);
  digitalWrite(pinVermelho, estado == 2);

  // BUZZER
  if (estado == 0) {

    noTone(pinBuzzer);

  }
  else if (estado == 1) {

    tone(pinBuzzer, 1000, 200);

  }
  else {

    tone(pinBuzzer, 3000);

  }

  // LCD
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(leitura);
  lcd.print("    ");

  lcd.setCursor(0, 1);

  if (estado == 0) {

    lcd.print("Status: BOM" );

  }
  else {

    lcd.print("Alerta: Temp Alta");

  }

  delay(500);
}