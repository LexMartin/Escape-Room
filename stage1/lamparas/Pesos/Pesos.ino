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




HX711 scale(A1, A0);	// parameter "gain" is ommited; the default value 128 is used by the library
HX711 Peso1(A2, A3);

const float Umbral=30.0;
const int PIN_OK = 4;

float Temp=0;

void setup() {
  Serial.begin(38400);
pinMode(PIN_OK,OUTPUT);
scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();		
}

void loop() {
  Temp=scale.get_units(3);
  Serial.println(Temp,1);
  if (Temp>Umbral)
    digitalWrite(PIN_OK,HIGH);
    else 
    digitalWrite(PIN_OK,LOW);
    
  
  scale.power_down();			        // put the ADC in sleep mode
  //delay(500);
  scale.power_up();
}
