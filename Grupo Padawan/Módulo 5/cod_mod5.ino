// Definição dos pinos
const int led1Pin = 7;   
const int led2Pin = 3;   
const int led3Pin = 4;   
const int buzzerPin = 5; 
const int sensorPin = 2; // Pino de interrupção por definição (Arduino)

unsigned long previousMillis = 0; 
const long interval = 100; 

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // Inicializa LEDs e buzzer
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(buzzerPin, LOW);

  // Configura a interrupção para o sensor de presença
  attachInterrupt(digitalPinToInterrupt(sensorPin), sensorInterrupt, CHANGE);
  Serial.begin(9600); 
}

void loop() {
  checkLeds();
}

void checkLeds() {
  unsigned long currentMillis = millis();

  // Pisca os LEDs 1 e 2 se o sensor não detectar presença
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (digitalRead(led1Pin) == LOW) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
    } else {
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
    }
  }
  digitalWrite(led3Pin, LOW);
  digitalWrite(buzzerPin, LOW);
}

// Função chamada pela interrupção
void sensorInterrupt() {
  // Manter LED verde (LED 3) ligado e buzzer tocando enquanto o sensor detectar presença
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  while (digitalRead(sensorPin) == HIGH) {
    digitalWrite(led3Pin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  }

  // Desligar LED verde e buzzer quando não houver mais presença
  digitalWrite(led3Pin, LOW);
  digitalWrite(buzzerPin, LOW);
}
