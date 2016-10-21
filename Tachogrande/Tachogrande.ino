//Librerias
#include <Wire.h>
#include <PCA9685.h>


//Definiciones
#define SerialRojo Serial1
#define SerialVerde Serial2
#define SerialAzul Serial3
#define On 0
#define Off 4096
#define Debug
#define Rojo 0
#define Verde 1
#define Azul 2


//Variables
/*int Control1[15] = {}; //R-V-A x5
  int Control2[15] = {}; //R-V-A x5
  int Control3[15] = {}; //R-V-A x5
  int Control4[15] = {}; //R-V-A x5
  int Control5[12] = {}; //R-V-A x4
*/

int Control[5][15];
int CantRojo = 0; //Altura del Rojo
int CantVerde = 0; //Altura del Verde
int CantAzul = 0; //Altura del Azul
int CantControlRojo = 0; //Segun la "altura" la cantida de controladoras que hay que tocar
int CantControlVerde = 0; //Segun la "altura" la cantida de controladoras que hay que tocar
int CantControlAzul = 0; //Segun la "altura" la cantida de controladoras que hay que tocar


//Constructores
PCA9685 Controlador1; //Tiras 1-2-3-4-5
PCA9685 Controlador2; //Tiras 6-7-8-9-10
PCA9685 Controlador3; //Tiras 11-12-13-14-15
PCA9685 Controlador4; //Tiras 16-17-18-19-20
PCA9685 Controlador5; //Toras 21-22-23-24


void setup() {

#ifdef debug
  Serial.begin(9600);
#endif

  SerialRojo.begin(9600);
  SerialVerde.begin(9600);
  SerialAzul.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  Controlador1.resetDevices();
  Controlador1.init();
  Controlador2.init();
  Controlador3.init();
  Controlador4.init();
  Controlador5.init();
}

void loop() {
  LeerSerials();
  Procesar();
  Recorrer();
  Actualizar();
}

void LeerSerials () {
  if (SerialRojo.available()) {
    CantRojo = SerialRojo.read();
  }
  if (SerialVerde.available()) {
    CantVerde = SerialVerde.read();
  }
  if (SerialAzul.available()) {
    CantAzul = SerialAzul.read();
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

#ifdef Debug
  Serial.println(CantControlRojo);
  Serial.println(CantControlVerde);
  Serial.println(CantControlAzul);
#endif
}

void Recorrer() {
  RecorrerControladoras(Rojo, CantRojo, CantControlRojo);
  RecorrerControladoras(Verde, CantVerde, CantControlVerde);
  RecorrerControladoras(Azul, CantAzul, CantControlAzul);
}

int RecorrerControladoras(int Sum, int CantColor, int CantCtrl) {
  int j = 0; //Inicio una variable para controlar la cantidad de veces que doy la vuelta.
  for (int i = 0; i <= CantCtrl-1; i ++) {
    for (int h = Sum; i <= 14; i + 3) {
      Control[i][h] = On;
      j++;
      if (j == CantColor) break;
    }
  }
  for (int i = CantCtrl-1 ; i <= 4; i++) {
    for (int h = Sum + (j - ((CantCtrl-1)* 5)) * 3; i <= 14 ; i + 3) {
      Control[i][h] = Off;
      j++;
      if (j == 24) break;
    }
  }
}

void Actualizar() {
  Controlador1.setChannelsPWM(0, 15, Control[1]);
  Controlador2.setChannelsPWM(0, 15, Control[2]);
  Controlador3.setChannelsPWM(0, 15, Control[3]);
  Controlador4.setChannelsPWM(0, 15, Control[4]);
  Controlador5.setChannelsPWM(0, 12, Control[5]);
}
