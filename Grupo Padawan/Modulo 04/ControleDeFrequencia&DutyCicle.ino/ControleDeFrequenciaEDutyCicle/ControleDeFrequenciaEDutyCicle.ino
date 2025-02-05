#include <avr/io.h>
#include <avr/interrupt.h>

const int pot1Pin = A0; // Potenciômetro para Frequência
const int pot2Pin = A4; // Potenciômetro para Duty Cycle (Ciclo de Trabalho)
const int pwmPin = 9;   // Pino de saída PWM (OC1A)

void setup() {
  Serial.begin(9600);

  pinMode(pwmPin, OUTPUT);

  // Configura o Timer1 para PWM Rápido (Fast PWM)
  TCCR1A = 0;
  TCCR1B = 0;

  // Modo não-inversor para OC1A (pino 9)
  TCCR1A |= (1 << COM1A1);

  // Modo PWM Rápido com ICR1 como valor TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);

  // Configura o prescaler para 64 (permite frequências mais baixas)
  TCCR1B |= (1 << CS11) | (1 << CS10);  // Prescaler de 64

  // Habilita interrupções globais
  sei();
}

void loop() {
  // Lê o valor do potenciômetro 1 (frequência) e mapeia para 10 - 500 Hz
  int pot1Value = analogRead(pot1Pin);
  int frequency = map(pot1Value, 0, 1023, 20, 500);

  // Calcula o valor TOP para a frequência desejada com prescaler de 64
  long topValue = 16000000 / (frequency * 64) - 1;

  // Define o valor TOP (afeta a frequência)
  ICR1 = topValue;

  // Lê o valor do potenciômetro 2 (duty cycle) e mapeia para 0 - 100%
  int pot2Value = analogRead(pot2Pin);
  int dutyCycle = map(pot2Value, 0, 1023, 0, 100);

  // Define o ciclo de trabalho (valor de comparação para OCR1A)
  OCR1A = (dutyCycle * topValue) / 100;

  // Saída de depuração para monitoramento
  Serial.println("frequencyValue = " + String(frequency) + "Hz\t dutyCicleValue = " + String(dutyCycle) + "%");

  delay(100); // Pequeno atraso para estabilidade
}