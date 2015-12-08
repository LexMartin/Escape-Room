#include "HX711.h"

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

//
//  Sensor de Peso 50Kg --------- HX711
//  Blanco ----------------------- E+
//  Negro  ----------------------- E- 
//  Blanco ---Resistencia---+
//                          +----- A-
//  Negro  ---Resistencia --+
//  Rojo   ----------------------- A+




HX711 Peso1(A1, A0);  
HX711 Peso2(A3, A2);
HX711 Peso3(A5, A4);
HX711 Peso4(A7, A6);
HX711 Peso5(A9, A8);
HX711 Peso6(A11, A10);
HX711 Peso7(A13, A11);
HX711 sensors[] = {Peso1,Peso2,Peso3,Peso4,Peso5,Peso6,Peso7};
const float Umbral=300.0;
const int PIN_OK = 4;

float Temp=0;
float umbrals[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int correctUmbral[] = {0,0,0,0,0,0,0};
void setup() {
  Serial.begin(38400);
pinMode(PIN_OK,OUTPUT);
//scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
//  scale.tare();		
Serial.print("SETUP");
float cal2 = 0;
 for (int i = 0; i < 7 ; i++){
      sensors[i].set_scale(107.f);
      sensors[i].tare();
   }
 Serial.print("Termina Setup");
 getUmbrals();
}

void loop() {
  //Serial.println("iNICIO DEL LOOP");

  int i = 0;
  int foo = readPIR2(i);
  Serial.println("");
  Serial.print("Lampara ");
  Serial.print(i);
  Serial.print(":");
  Serial.print(foo);

}


float readPIR2(int index){
  float tmp = pow(sensors[index].get_units(3),2);
  float dif = tmp - umbrals[index];
  if(dif > 35000.0 && correctUmbral[index] == 0){
    umbrals[index] = tmp;
    correctUmbral[index] = 1;
  }
  
  
  float compare = sqrt(pow(tmp -umbrals[index],2));
  
  float estimate = umbrals[index]+(umbrals[index]* 0.05); 
  
  int result = 0;
  
  result = compare > 20000.0 ? 1:0;
  
  sensors[index].power_down();              // put the ADC in sleep mode
  //delay(5000);
  sensors[index].power_up();
  return tmp;  
}
int readPIR(int index)
{
  
  float tmp = sensors[index].get_units(3);
  
  int result = tmp > Umbral ? 1:0;
  sensors[index].power_down();              // put the ADC in sleep mode
  //delay(5000);
  sensors[index].power_up();
  return result;  
}


void getUmbrals(){
   float cal2 = 0;
   for (int i = 0; i < 7; i++){
  
        cal2=sensors[i].get_units(3);
         umbrals[i] = pow(cal2,2);
          delay(100);     
   }
}
