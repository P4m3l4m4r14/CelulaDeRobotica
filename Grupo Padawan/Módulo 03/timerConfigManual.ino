const int ledPin = 13; // Pino do LED embutido

void setup() {
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
  noInterrupts(); // Desativa todas as interrupções

  // Configura o Timer 1 no modo CTC (Clear Timer on Compare Match)
  TCCR1A = 0;        // Limpa o registrador de controle A
  TCCR1B = 0;        // Limpa o registrador de controle B
  TCNT1  = 0;        // Inicializa o contador do Timer 1 com 0

  // Define o valor de comparação para gerar uma interrupção a cada 1 segundo
  // F_CPU / (prescaler * frequência desejada) - 1
  OCR1A = 15624;     // Para 1 segundo com prescaler 1024

  TCCR1B |= (1 << WGM12);   // Modo CTC (limpar o timer ao comparar)
  TCCR1B |= (1 << CS12) | (1 << CS10); // Configura prescaler 1024

  TIMSK1 |= (1 << OCIE1A);  // Habilita interrupção por comparação
  interrupts();             // Ativa as interrupções
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(ledPin, !digitalRead(ledPin)); // Inverte o estado do LED
}

void loop() {
  // O código principal continua rodando normalmente
}