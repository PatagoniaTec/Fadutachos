//Librerias
#include <SoftwareSerial.h>


//Definiciones
#define Pir 4
#define Sensor A0
#define Umbral 250
#define Blanco 5
#define Color 6
#define Delay 100
#define Timeout 5000


//Variables
long Tiempo = 0;
int ValorSensor = 0;


//Constructores
SoftwareSerial RS485(7 , 8); // Rx-Tx para la comunicacion con el tacho grande.

void setup() {
  RS485.begin(9600);
  pinMode(Pir , INPUT);
  pinMode(Blanco , OUTPUT);
  pinMode(Color , OUTPUT);
}

void loop() {
  RS485.println(0);
  if (digitalRead(Pir) == 0) {
    int PWM = 0;
    int SubeBaja = 0;
    while (digitalRead(Pir) == 0) {
      if (SubeBaja == 0) PWM++;
      if (SubeBaja == 1) PWM--;
      analogWrite(Blanco, PWM);
      delay(Delay);
      if (PWM == 255) SubeBaja = 1;
      if (PWM == 0) SubeBaja = 0;
    }
    digitalWrite(Blanco, LOW);
  }
  if (digitalRead(Pir) == 1) {
    digitalWrite(Color, HIGH);
    Tiempo = millis();
    while (millis() - Tiempo < Timeout) {
      ValorSensor = analogRead(Sensor);
      if (ValorSensor > Umbral) {
        Tiempo = millis();
        int i = map (ValorSensor, Umbral, 1023 , 1 , 24);
        RS485.println(i);
      }
    }
  }
}
