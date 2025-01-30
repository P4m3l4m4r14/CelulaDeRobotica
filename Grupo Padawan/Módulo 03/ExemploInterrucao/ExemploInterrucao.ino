const int buttonPin = 2;  // Pino onde o botão está conectado (usa interrupt 0)
const int ledPin = 13;    // Pino para o LED embutido
volatile bool ledState = false;   // Variável volátil para armazenar o estado do LED
volatile bool printSerial = false; // Flag para controlar o print serial

void setup() {
  pinMode(buttonPin, INPUT);   // Configura o pino do botão como entrada
  pinMode(ledPin, OUTPUT);     // Configura o pino do LED como saída
  Serial.begin(9600);          // Inicializa a comunicação serial para depuração

  // Associa a interrupção ao botão (Interrupt 0 no pino 2)
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLED, RISING);
}

void loop() {
  // Escreve o estado do LED na saída
  digitalWrite(ledPin, ledState);

  // Verifica se a flag printSerial está ativa para imprimir a mensagem
  if (printSerial) {
    printSerial = false;  // Reseta a flag
    Serial.println("sBotão pressionado!");
  }

  delay(2000);  // Pausa de 2 segundos (para demonstrar que o código principal continua rodando)
}

// Função de interrupção (ISR) que será chamada quando o botão for pressionado
void toggleLED() {
  ledState = !ledState;  // Inverte o estado do LED
  printSerial = true;    // Define a flag para realizar o print no loop
}
