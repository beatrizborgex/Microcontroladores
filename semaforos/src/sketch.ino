//Autor(a): Beatriz Borges de Oliveira
//Curso: Engenharia de Computação

const int semaforoVermelho1 = 13;
const int semaforoAmarelo1 = 12;
const int semaforoVerde1 = 11;
const int semaforoVermelho2 = 7;
const int semaforoAmarelo2 = 6;
const int semaforoVerde2 = 5;

const int semaforoPedestreVermelho = 9;
const int semaforoPedestreVerde = 8;

const int botaoPedestre = 3;

int estadoSemaforo = 0;
bool pedestreAtivo = false;
bool modoAmareloPiscando = false;
unsigned long tempoPressionado = 0;

void setup() {
  Serial.begin(9600);
  pinMode(semaforoVermelho1, OUTPUT);
  pinMode(semaforoAmarelo1, OUTPUT);
  pinMode(semaforoVerde1, OUTPUT);
  pinMode(semaforoVermelho2, OUTPUT);
  pinMode(semaforoAmarelo2, OUTPUT);
  pinMode(semaforoVerde2, OUTPUT);

  pinMode(semaforoPedestreVermelho, OUTPUT);
  pinMode(semaforoPedestreVerde, OUTPUT);

  pinMode(botaoPedestre, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(botaoPedestre), botaoPedestrePressionado, FALLING);
}

void desligarSemaforosDeTrafego() {
  digitalWrite(semaforoVermelho1, HIGH);
  digitalWrite(semaforoAmarelo1, LOW);
  digitalWrite(semaforoVerde1, LOW);
  digitalWrite(semaforoVermelho2, HIGH);
  digitalWrite(semaforoAmarelo2, LOW);
  digitalWrite(semaforoVerde2, LOW);
  digitalWrite(semaforoPedestreVermelho, LOW);
  delay(3000);
  estadoSemaforo = 0;
}

void modoPiscar (){
  digitalWrite(semaforoVermelho1, LOW);
  digitalWrite(semaforoVerde1, LOW);
  digitalWrite(semaforoVermelho2, LOW);
  digitalWrite(semaforoVerde2, LOW);
  digitalWrite(semaforoPedestreVermelho, LOW);
  delay(200);
  estadoSemaforo = 4;
}

void botaoPedestrePressionado() {
  if (!pedestreAtivo) {
    pedestreAtivo = true;
    tempoPressionado = millis();
    desligarSemaforosDeTrafego();
    digitalWrite(semaforoPedestreVerde, HIGH);
  }
}

void loop() {
  if (pedestreAtivo) {
    unsigned long tempoAtual = millis();
    if (tempoAtual - tempoPressionado >= 3000) { 
      pedestreAtivo = false;
      digitalWrite(semaforoPedestreVerde, LOW);
      estadoSemaforo = 0;
    }
  } else {
    while (Serial.available() > 0) {
      String comando = Serial.readString();
      if (comando == "amarelo") {
        modoAmareloPiscando = true;
      } else if (comando == "semáforo") {
        estadoSemaforo = 1;
        modoAmareloPiscando = false;
      }
    }

    if (modoAmareloPiscando) {
      modoPiscar();
      digitalWrite(semaforoAmarelo1, !digitalRead(semaforoAmarelo1));
      digitalWrite(semaforoAmarelo2, !digitalRead(semaforoAmarelo2));
    } else {
      switch (estadoSemaforo) {
        case 0:
          digitalWrite(semaforoPedestreVermelho, HIGH);
          digitalWrite(semaforoVermelho1, HIGH);
          digitalWrite(semaforoAmarelo1, LOW);
          digitalWrite(semaforoVerde1, LOW);
          digitalWrite(semaforoVermelho2, LOW);
          digitalWrite(semaforoAmarelo2, LOW);
          digitalWrite(semaforoVerde2, HIGH);
          delay(2000);
          estadoSemaforo = 1;
          break;
        case 1:
          digitalWrite(semaforoPedestreVermelho, HIGH);
          digitalWrite(semaforoVermelho1, HIGH);
          digitalWrite(semaforoAmarelo1, LOW);
          digitalWrite(semaforoVerde1, LOW);
          digitalWrite(semaforoVermelho2, LOW);
          digitalWrite(semaforoAmarelo2, HIGH);
          digitalWrite(semaforoVerde2, LOW);
          delay(2000);
          estadoSemaforo = 2;
          break;
        case 2:
          digitalWrite(semaforoPedestreVermelho, HIGH);
          digitalWrite(semaforoVermelho1, LOW);
          digitalWrite(semaforoAmarelo1, LOW);
          digitalWrite(semaforoVerde1, HIGH);
          digitalWrite(semaforoVermelho2, HIGH);
          digitalWrite(semaforoAmarelo2, LOW);
          digitalWrite(semaforoVerde2, LOW);
          delay(2000);
          estadoSemaforo = 3;
          break;
        case 3:
          digitalWrite(semaforoPedestreVermelho, HIGH);
          digitalWrite(semaforoVermelho1, LOW);
          digitalWrite(semaforoAmarelo1, HIGH);
          digitalWrite(semaforoVerde1, LOW);
          digitalWrite(semaforoVermelho2, HIGH);
          digitalWrite(semaforoAmarelo2, LOW);
          digitalWrite(semaforoVerde2, LOW);
          delay(2000);
          estadoSemaforo = 0;
          break;
      }
    }
  }
}
