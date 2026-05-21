# 🍷 Vinheria Agnello — Monitor Ambiental com Arduino

Sistema de monitoramento ambiental para a Vinheria Agnello, desenvolvido com Arduino Uno. O projeto combina sensores de **temperatura/umidade (DHT22)** e **luminosidade (LDR)** com feedback visual (LEDs), sonoro (Buzzer) e textual (Display LCD 16x2).

https://youtu.be/9yAoD34qhvE?si=HEgTdz90to-aNpd1

---

## 📋 Componentes Utilizados

| Componente       | Quantidade | Descrição                                      |
|------------------|------------|------------------------------------------------|
| Arduino Uno      | 1          | Microcontrolador principal                     |
| DHT22            | 1          | Sensor de temperatura e umidade digital        |
| LDR              | 1          | Sensor de luminosidade analógico               |
| Display LCD 16x2 | 1          | Exibição de leituras e alertas em tempo real   |
| LED Verde        | 1          | Indica temperatura baixa (< 18°C)              |
| LED Amarelo      | 1          | Indica temperatura média (18°C – 29°C)         |
| LED Vermelho     | 1          | Indica temperatura alta (≥ 30°C)               |
| Buzzer           | 1          | Alerta sonoro em temperatura alta              |
| Resistores       | 4+         | Para os LEDs e LDR                             |
| Protoboard       | 1          | Montagem dos componentes                       |
| Jumpers          | —          | Conexões entre componentes e Arduino           |

---

## 🔌 Pinagem

| Componente     | Pino Arduino |
|----------------|--------------|
| LED Verde      | D2           |
| LED Amarelo    | D3           |
| LED Vermelho   | D4           |
| Buzzer         | D5           |
| LCD D4         | D6           |
| LCD D5         | D7           |
| LCD D6         | D8           |
| LCD D7         | D9           |
| DHT22 (DATA)   | D10          |
| LCD EN         | D11          |
| LCD RS         | D13          |
| LDR            | A5           |

---

## 🌡️ Sensor DHT22

O DHT22 é um sensor digital de temperatura e umidade de alta precisão, superior ao DHT11 por sua maior resolução e faixa de medição.

### Especificações técnicas

| Parâmetro         | DHT22                  |
|-------------------|------------------------|
| Tensão de operação| 3.3V – 5V              |
| Faixa temperatura | -40°C a +80°C          |
| Precisão temp.    | ±0.5°C                 |
| Faixa umidade     | 0% – 100% RH           |
| Precisão umidade  | ±2% RH                 |
| Protocolo         | 1-Wire (digital)       |
| Intervalo leitura | Mínimo 2 segundos      |

### Biblioteca e inicialização

A biblioteca `DHT.h` deve ser instalada via Library Manager do Arduino IDE (buscar por **"DHT sensor library" — Adafruit**).

```cpp
#include <DHT.h>

#define DHTPIN  10
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
}
```

### Leitura dos dados

```cpp
float temperatura = dht.readTemperature(); // em °C
float umidade     = dht.readHumidity();    // em %
```

> ⚠️ O DHT22 precisa de **no mínimo 2 segundos** entre leituras. Por isso o `delay(2000)` ao final do `loop()` é essencial — leituras mais rápidas retornam `NaN`.

---

## 📟 Display LCD 16x2

O LCD exibe em tempo real os dados dos dois sensores e alertas de ambiente.

### Inicialização

```cpp
#include <LiquidCrystal.h>

// Ordem: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(13, 11, 9, 8, 7, 6);

lcd.begin(16, 2);
```

### Mensagem de Boot

Ao ligar, o sistema exibe por 2 segundos:

```
Sistema ON
Inicializando
```

### Exibição em Loop

| Linha   | Conteúdo padrão             | Exemplo           |
|---------|-----------------------------|-------------------|
| Linha 1 | Temperatura e Umidade       | `T:24.50C U:65%`  |
| Linha 2 | Luminosidade ou alerta      | `Luz:820`         |
| Linha 2 | Alerta de pouca luz         | `Ambiente Escuro` |

> Quando `luminosidade < 300`, a linha 2 é sobrescrita com `Ambiente Escuro`.

---

## 💡 Lógica de Estados

### Temperatura (DHT22)

| Estado  | Condição         | LED Ativo   | Buzzer              |
|---------|------------------|-------------|---------------------|
| BAIXA   | `temp < 18°C`    | 🟢 Verde    | Desligado           |
| MÉDIA   | `18°C ≤ temp < 30°C` | 🟡 Amarelo | Desligado        |
| ALTA    | `temp ≥ 30°C`    | 🔴 Vermelho | Contínuo (1000 Hz)  |

### Luminosidade (LDR)

| Condição          | Ação no LCD              |
|-------------------|--------------------------|
| `lux ≥ 300`       | Exibe valor numérico     |
| `lux < 300`       | Exibe `Ambiente Escuro`  |

---

## 🗂️ Estrutura do Código

```
setup()
├── Configura pinos (LEDs e Buzzer) como OUTPUT
├── Inicia LCD (16x2)
├── Inicia DHT22
└── Exibe mensagem de boot por 2s

loop()
├── Lê temperatura e umidade (DHT22)
├── Lê luminosidade (LDR → A5)
├── Atualiza LCD
│   ├── Linha 1: T:xx.xxC  U:xx%
│   └── Linha 2: Luz:xxxx ou Ambiente Escuro
├── Controla LEDs conforme temperatura
├── Controla Buzzer (ON se temp ≥ 30°C)
└── Aguarda 2000ms
```

---

## 🚀 Como Simular (Wokwi)

1. Acesse [wokwi.com](https://wokwi.com) e crie um novo projeto **Arduino Uno**.
2. Adicione os componentes conforme a pinagem acima.
3. No arquivo `libraries.txt`, adicione:
   ```
   DHT sensor library
   Adafruit Unified Sensor
   ```
4. Cole o código no editor.
5. Clique em **▶ Play** para iniciar a simulação.
6. Clique no DHT22 para ajustar temperatura e umidade em tempo real.
7. Clique no LDR para simular variações de luminosidade.

---

## 📦 Dependências

| Biblioteca              | Origem   | Instalação                                    |
|-------------------------|----------|-----------------------------------------------|
| `LiquidCrystal.h`       | Nativa   | Já incluída no Arduino IDE                    |
| `DHT.h`                 | Adafruit | Library Manager → "DHT sensor library"        |
| `Adafruit_Sensor.h`     | Adafruit | Library Manager → "Adafruit Unified Sensor"   |

---

## 👥 Equipe

| Nome              | RM     |
|-------------------|--------|
| Gabriel Juarez    | 563680 |
| Henrique da Silva | 569137 |
| Nicolas Marçal    | 571510 |
| Andrey Luigi      | 569575 |
| Lucas Trevisan    | 569731 |

**Curso:** Engenharia de Software — FIAP  
**Disciplina:** Computational Thinking with Arduino

---

## 📄 Licença

Projeto acadêmico desenvolvido para fins educacionais na FIAP. Uso livre para estudo e adaptação.
