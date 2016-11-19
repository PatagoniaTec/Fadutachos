//Librerias
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Definiciones
#define SerialRojo Serial1
#define SerialVerde Serial2
#define SerialAzul Serial3
#define On 4095
#define Off 0
#define Debug
#define Rojo 0
#define Verde 1
#define Azul 2

#define PlanB



//Variables
int CantRojo = 0; //Altura del Rojo
int CantVerde = 0; //Altura del Verde
int CantAzul = 0; //Altura del Azul
int CantControlRojo = 0; //Segun la "altura" la cantida de pwmas que hay que tocar
int CantControlVerde = 0; //Segun la "altura" la cantida de pwmas que hay que tocar
int CantControlAzul = 0; //Segun la "altura" la cantida de pwmas que hay que tocar


//Constructores
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x44);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x48);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver();

void setup() {

#ifdef Debug
  Serial.begin(115200);
#endif

  SerialRojo.begin(115200);
  SerialVerde.begin(115200);
  SerialAzul.begin(115200);
  pwm1.begin();
  pwm1.setPWMFreq(1600);
  pwm2.begin();
  pwm2.setPWMFreq(1600);
  pwm3.begin();
  pwm3.setPWMFreq(1600);
  pwm4.begin();
  pwm4.setPWMFreq(1600);
  pwm5.begin();
  pwm5.setPWMFreq(1600);
}

void loop() {
  LeerSerials();
  Procesar();
  Recorrer();
}

void LeerSerials () {
  Serial.println("leyendo serials");
  if (SerialRojo.available()) {
    CantRojo = SerialRojo.parseInt();
    Serial.println(CantRojo);
  }
  if (SerialVerde.available()) {
    CantVerde = SerialVerde.parseInt();
    Serial.println(CantVerde);
  }
  if (SerialAzul.available()) {
    CantAzul = SerialAzul.parseInt();
    Serial.println(CantAzul);
  }
}

void Procesar() {
  if (CantRojo == 0) CantControlRojo = 0;
  if (CantRojo > 0 && CantRojo < 6) CantControlRojo = 1;
  if (CantRojo > 5 && CantRojo < 11) CantControlRojo = 2;
  if (CantRojo > 10 && CantRojo < 16) CantControlRojo = 3;
  if (CantRojo > 15 && CantRojo < 21) CantControlRojo = 4;
  if (CantRojo > 20 && CantRojo < 25) CantControlRojo = 5;
  if (CantVerde == 0) CantControlVerde = 0;
  if (CantVerde > 0 && CantVerde < 6) CantControlVerde = 1;
  if (CantVerde > 5 && CantVerde < 11) CantControlVerde = 2;
  if (CantVerde > 10 && CantVerde < 16) CantControlVerde = 3;
  if (CantVerde > 15 && CantVerde < 21) CantControlVerde = 4;
  if (CantVerde > 20 && CantVerde < 25) CantControlVerde = 5;
  if (CantAzul == 0) CantControlAzul = 0;
  if (CantAzul > 0 && CantAzul < 6) CantControlAzul = 1;
  if (CantAzul > 5 && CantAzul < 11) CantControlAzul = 2;
  if (CantAzul > 10 && CantAzul < 16) CantControlAzul = 3;
  if (CantAzul > 15 && CantAzul < 21) CantControlAzul = 4;
  if (CantAzul > 20 && CantAzul < 25) CantControlAzul = 5;

  /*#ifdef Debug
    Serial.println(CantControlRojo);
    Serial.println(CantControlVerde);
    Serial.println(CantControlAzul);
    #endif*/
}

void Recorrer() {
  Recorrerpwmas(Rojo, CantRojo, CantControlRojo);
  Recorrerpwmas(Verde, CantVerde, CantControlVerde);
  Recorrerpwmas(Azul, CantAzul, CantControlAzul);
}

int Recorrerpwmas(int Sum, int CantColor, int CantCtrl) {
  if (CantCtrl == 0) {
    for (int i = 1; i <= 5; i ++) {
      for (int h = Sum; h <= 14; h += 3) {
        if (i == 1) pwm1.setPWM(h, 4095, 0);
        if (i == 2) pwm2.setPWM(h, 4095, 0);
        if (i == 3) pwm3.setPWM(h, 4095, 0);
        if (i == 4) pwm4.setPWM(h, 4095, 0);
        if (i == 5) pwm5.setPWM(h, 4095, 0);
      }
    }
  } else {
    int j = 0; //Inicio una variable para controlar la cantidad de veces que doy la vuelta.
    for (int i = 1; i <= CantCtrl; i++) {
      for (int h = Sum; h <= 14; h += 3) {
        if (j >= CantColor) break;
        j++;
        /*#ifdef Debug
                Serial.println("Recorriendo ON");
                Serial.println(j);
          #endif*/
        if (i == 1) pwm1.setPWM(h, 0, 4095);
        if (i == 2) pwm2.setPWM(h, 0, 4095);
        if (i == 3) pwm3.setPWM(h, 0, 4095);
        if (i == 4) pwm4.setPWM(h, 0, 4095);
        if (i == 5) pwm5.setPWM(h, 0, 4095);
      }
    }
    int k = Sum + ((j - ((CantCtrl - 1) * 5)) * 3);
    Serial.println(k);
    for (int i = CantCtrl; i <= 5; i++) {
      for (k ; k <= 14 ; k += 3) {
        if (j == 24) break;
        j++;
        /*#ifdef Debug
                Serial.println("Recorriendo Off");
                Serial.println(j);
                Serial.println(i);
          #endif*/
        if (i == 1) pwm1.setPWM(k, 4095, 0);
        if (i == 2) pwm2.setPWM(k, 4095, 0);
        if (i == 3) pwm3.setPWM(k, 4095, 0);
        if (i == 4) pwm4.setPWM(k, 4095, 0);
        if (i == 5) pwm5.setPWM(k, 4095, 0);
      }
      k = Sum;
    }
  }
}
