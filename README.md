# 💡 Monitor de Luminosidade com Arduino

Projeto de monitoramento de luminosidade ambiente utilizando sensor LDR, display LCD 16x2, LEDs indicadores e buzzer. Desenvolvido para a disciplina de **Engenharia de Software**.

---

## 📋 Descrição

O sistema lê continuamente a intensidade de luz do ambiente através de um sensor LDR (Light Dependent Resistor) e classifica o nível em três estados:

| Estado | Condição (leitura analógica) | LED ativo | Buzzer |
|--------|------------------------------|-----------|--------|
| **BOM** | > 850 | Verde | Silencioso |
| **MÉDIA** | 400 – 850 | Amarelo | Bipe intermitente (1000 Hz) |
| **RUIM** | < 400 | Vermelho | Tom contínuo (3000 Hz) |

O estado atual é exibido no LCD junto com o valor bruto da leitura.

---

## 🛠️ Hardware necessário

- 1× Arduino Uno (ou compatível)
- 1× Sensor LDR
- 1× Resistor de 10 kΩ (divisor de tensão para o LDR)
- 1× Display LCD 16×2 (compatível com LiquidCrystal)
- 1× LED Verde
- 1× LED Amarelo
- 1× LED Vermelho
- 3× Resistores de 220 Ω (para os LEDs)
- 1× Buzzer passivo
- Jumpers e protoboard

---

## 🔌 Mapeamento de pinos

| Componente | Pino Arduino |
|------------|-------------|
| LCD RS | 2 |
| LCD Enable | 3 |
| LCD D4 | 4 |
| LCD D5 | 5 |
| LCD D6 | 6 |
| LCD D7 | 7 |
| LED Verde | 8 |
| LED Amarelo | 9 |
| LED Vermelho | 10 |
| Buzzer | 11 |
| LDR | A0 |

---

## 📦 Dependências

- [LiquidCrystal](https://www.arduino.cc/reference/en/libraries/liquidcrystal/) — biblioteca padrão da Arduino IDE (já incluída).

---

## 🚀 Como usar

1. Monte o circuito conforme o mapeamento de pinos acima.
2. Abra o arquivo `.ino` na **Arduino IDE**.
3. Selecione a placa e a porta serial corretas em **Ferramentas**.
4. Clique em **Upload** para carregar o código.
5. Ao iniciar, o LCD exibirá a mensagem `Eng. Software / Monitor Luz` por 2 segundos.
6. Em seguida, o monitor exibirá em tempo real o valor do sensor e o status de luminosidade.

Você também pode acompanhar os valores brutos do LDR pelo **Monitor Serial** a 9600 bps.

---

## 🧠 Lógica de funcionamento

```
setup()
  ├── Configura pinos dos LEDs e buzzer como OUTPUT
  ├── Inicia comunicação serial (9600 bps)
  └── Exibe mensagem de boas-vindas no LCD por 2s

loop()  (executa a cada 500 ms)
  ├── Lê valor analógico do LDR (0–1023)
  ├── Classifica em estado: BOM / MÉDIA / RUIM
  ├── Aciona o LED correspondente
  ├── Controla o buzzer conforme o estado
  └── Atualiza o display LCD
```

---

## 📁 Estrutura do projeto

```
monitor-luminosidade/
├── monitor_luminosidade.ino   # Código principal
└── README.md
```

---

## 👥 Integrantes

- Henrique da Silva — RM: 569137
- Andrey Luigi — RM: 569575
- Nicolas Moreira Silva — RM: 571510
- Gabriel Juarez — RM: 563680
- Lucas Trevisan — RM: 569731

---
