#define LED_BUILTIN 5
char buf;

void setup() {
  // Definir os pinos dos leds como saída
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
 buf = Serial.read(); //se receber 1 led liga
 if(buf == 1){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Led Ligado!!!");
 }else{
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Led desligado!!!");
 }
}

//Baixar APK no celular para comunicar : Arduíno Bluetooth controller
