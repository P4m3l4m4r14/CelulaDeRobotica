
#include <Servo.h>

#define potentiometerPin A0
#define servoPin 5

int potentiometerValue = 0;
int servoTiming = 0;
int defaultPotentiometerValue = 0;

unsigned long lastTime =0;

Servo servoMotor;

void setup() {
  Serial.begin(9600);

  pinMode(servoPin, OUTPUT);
  pinMode (potentiometerPin, INPUT);
  defaultPotentiometerValue = analogRead(potentiometerPin);

  servoMotor.attach(servoPin);
}

void loop() {
  potentiometerValue = analogRead(potentiometerPin);
  servoTiming = map(potentiometerValue, 0, 1024, 1000, 2000);
  servoMotor.writeMicroseconds(servoTiming);

  if(millis() - lastTime > 1000) {
    lastTime = millis();
    String message = "Potentiometer: " + String(potentiometerValue) + "\n" + "Servo Timing: " + String(servoTiming) + "us\n";
    Serial.println(message);
  }
}
