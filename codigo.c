// Projeto Arduino UNO - Monitor de Ambiente
// Componentes:
// - Sensor DHT22
// - Sensor LDR
// - LCD 16x2
// - LEDs (vermelho, amarelo, verde)
// - Buzzer

#include <LiquidCrystal.h>
#include <DHT.h>

// -------------------- PINOS --------------------

// LEDs
#define LED_VERMELHO 4
#define LED_AMARELO  3
#define LED_VERDE    2

// Buzzer
#define BUZZER 5

// LDR
#define LDR_PIN A5

// DHT22
#define DHTPIN 10
#define DHTTYPE DHT22

// LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(13, 11, 9, 8, 7, 6);

// Inicializa DHT
DHT dht(DHTPIN, DHTTYPE);

// -------------------- VARIÁVEIS --------------------

float temperatura;
float umidade;
int luminosidade;

// -------------------- SETUP --------------------

void setup() {

  // LEDs
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // LCD
  lcd.begin(16, 2);

  // DHT
  dht.begin();

  // Mensagem inicial
  lcd.setCursor(0, 0);
  lcd.print("Sistema ON");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando");

  delay(2000);
  lcd.clear();
}

// -------------------- LOOP --------------------

void loop() {

  // Leitura do DHT22
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  // Leitura do LDR
  luminosidade = analogRead(LDR_PIN);

  // ---------------- LCD ----------------

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura);
  lcd.print("C ");

  lcd.print("U:");
  lcd.print(umidade);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Luz:");
  lcd.print(luminosidade);

  // ---------------- CONTROLE LEDs ----------------

  // Apaga todos primeiro
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  // Temperatura baixa
  if (temperatura < 18) {

    digitalWrite(LED_VERDE, HIGH);
    noTone(BUZZER);

  }

  // Temperatura media
  else if (temperatura >= 18 && temperatura < 30) {

    digitalWrite(LED_AMARELO, HIGH);
    noTone(BUZZER);

  }

  // Temperatura alta
  else {

    digitalWrite(LED_VERMELHO, HIGH);

    // Liga buzzer
    tone(BUZZER, 1000);

  }

  // Alerta de pouca luz
  if (luminosidade < 300) {

    lcd.setCursor(0, 1);
    lcd.print("Ambiente Escuro");

  }

  delay(2000);
}