const int buttonPin = 2;  // Pino onde o botão está conectado
const int ledPin = 13;    // Pino para o LED embutido

void setup() {
  pinMode(buttonPin, INPUT);   // Configura o pino do botão como entrada
  pinMode(ledPin, OUTPUT);     // Configura o pino do LED como saída
  Serial.begin(9600);          // Inicializa a comunicação serial para depuração
}

void loop() {
  bool ledState = false; // Variável para armazenar o estado do led
  int buttonState = digitalRead(buttonPin); // Lê o estado do botão

  // Verifica se o botão foi pressionado
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado!");
    ledState = !ledState; // Troca o estado do LED
  }

  digitalWrite(ledPin, ledState); // Escreve o estado do led

  delay(2000);  // Pausa de 2 segundos no loop
}