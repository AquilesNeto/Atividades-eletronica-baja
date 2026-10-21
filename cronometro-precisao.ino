#define LED 3
#define BOTAO1 4
#define BOTAO2 2

bool rodando = false;
unsigned long tempoInicio = 0;
unsigned long tempoDecorrido = 0;

int estadoAnteriorBotao1 = HIGH;
int ultimoEstadoBotao1 = HIGH;
unsigned long ultimoTempoDebounce1 = 0;

unsigned long ultimoTempoDisplay = 0;

volatile bool lapSolicitado = false;
volatile unsigned long tempoLapCapturado = 0;
volatile unsigned long ultimoTempoInterrupcao = 0;

void tratarInterrupcaoLap() {
  unsigned long tempoAtual = millis();
  if (tempoAtual - ultimoTempoInterrupcao > 200) {
    if (rodando) {
      tempoLapCapturado = tempoAtual - tempoInicio;
      lapSolicitado = true;
    }
    ultimoTempoInterrupcao = tempoAtual;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(BOTAO1, INPUT_PULLUP);
  pinMode(BOTAO2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BOTAO2), tratarInterrupcaoLap, FALLING);

  digitalWrite(LED, LOW);
  Serial.println("Pressione o botao 1 para iniciar.");
}

void loop() {
  int leituraAtualBotao1 = digitalRead(BOTAO1);

  if (leituraAtualBotao1 != ultimoEstadoBotao1) {
    ultimoTempoDebounce1 = millis();
  }

  if ((millis() - ultimoTempoDebounce1) > 50) {
    if (leituraAtualBotao1 != estadoAnteriorBotao1) {
      estadoAnteriorBotao1 = leituraAtualBotao1;

      if (estadoAnteriorBotao1 == LOW) {
        rodando = !rodando; 

        if (rodando) {
          tempoInicio = millis();
          digitalWrite(LED, HIGH);
          Serial.println("\n--- Cronometro Iniciado ---");
        } else {
          digitalWrite(LED, LOW);
          Serial.println("\n--- Cronometro Parado / Resetado ---");
          Serial.println("Pressione o botao 1 para iniciar.");
        }
      }
    }
  }

  ultimoEstadoBotao1 = leituraAtualBotao1;

  if (rodando) {
    if (millis() - ultimoTempoDisplay >= 100) {
      ultimoTempoDisplay = millis();
      tempoDecorrido = millis() - tempoInicio;
      Serial.print("Tempo: ");
      Serial.print(tempoDecorrido / 1000.0, 2);
      Serial.println(" s");
    }
  }

  if (lapSolicitado) {
    lapSolicitado = false;
    Serial.print(">> LAP: ");
    Serial.print(tempoLapCapturado / 1000.0, 3);
    Serial.println(" s <<");
  }
} // CHAVE ADICIONADA AQUI
