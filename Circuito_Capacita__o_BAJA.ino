const int ledVermelho = 3;
const int ledAmarelo = 5;
const int ledVerde = 6;
const int botao = 2;

int estado = 0;
int qtdPress = 0;

unsigned long tempoAnterior = 0;
int brilhoAmarelo = 255;
int direcao = -5;

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(botao, INPUT); 
}

void loop() {
  estado = digitalRead(botao);
   if (estado == HIGH) {
        qtdPress+=1;
    delay(500);
    }else if(qtdPress == 4){
      qtdPress = 0;
    }
  if(qtdPress == 1) {
    analogWrite(ledVerde, 150);
  }else{
    analogWrite(ledVerde, 0);
  }
  
  if (qtdPress == 2) {
    if (millis() - tempoAnterior >= 10) {
      tempoAnterior = millis();
      
      brilhoAmarelo += direcao;

      if (brilhoAmarelo <= 0 || brilhoAmarelo >= 255) {
        direcao = -direcao;
      }
    }
    analogWrite(ledAmarelo, brilhoAmarelo);
  } else {
    analogWrite(ledAmarelo, 0);
    brilhoAmarelo = 255;
    direcao = -5;
  }
  
  if(qtdPress == 3) {
    analogWrite(ledVermelho, 255);
  }else{
    analogWrite(ledVermelho, 0);
  }
}
