#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ================= LEDs =================

#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_VERMELHO 4

// ================= Buzzer =================

#define BUZZER 5

// ================= LDR =================

#define LDR_PIN A0

// ================= DHT =================

#define DHTPIN 10
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ================= LCD =================

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= Variáveis =================

float temperatura;
float umidade;
int luminosidade;

void setup() {

  Serial.begin(9600);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();

  dht.begin();

  lcd.setCursor(0,0);
  lcd.print("Sistema ON");

  lcd.setCursor(0,1);
  lcd.print("Inicializando");

  delay(2000);

  lcd.clear();
}

void loop() {

  // ================= Leituras =================

  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  luminosidade = analogRead(LDR_PIN);

  // ================= Verifica erro =================

  if (isnan(temperatura) || isnan(umidade)) {

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Erro no DHT");

    delay(2000);

    return;
  }

  // ================= LCD =================

  lcd.clear();

  // Linha 1
  lcd.setCursor(0,0);

  lcd.print("T:");
  lcd.print(temperatura,1);

  lcd.print(" U:");
  lcd.print(umidade,0);

  // ================= LEDs =================

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  noTone(BUZZER);

  // =================================================
  // AMBIENTE ESCURO
  // =================================================

  if (luminosidade > 700) {

    lcd.setCursor(0,1);
    lcd.print("Amb Escuro");

    // LED VERDE
    digitalWrite(LED_VERDE, HIGH);
  }

  // =================================================
  // AMBIENTE MODERADO
  // =================================================

  else if (luminosidade > 300 && luminosidade <= 700) {

    lcd.setCursor(0,1);
    lcd.print("Amb Moderado");

    // LED AMARELO
    digitalWrite(LED_AMARELO, HIGH);

    // Bip intervalado
    tone(BUZZER, 1000);

    delay(200);

    noTone(BUZZER);

    delay(800);
  }

  // =================================================
  // AMBIENTE CLARO
  // =================================================

  else {

    lcd.setCursor(0,1);
    lcd.print("Amb Claro");

    // LED VERMELHO
    digitalWrite(LED_VERMELHO, HIGH);

    // Bip mais rápido
    tone(BUZZER, 1500);

    delay(100);

    noTone(BUZZER);

    delay(300);
  }

  delay(1000);
}