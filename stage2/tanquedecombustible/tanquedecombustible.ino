#include <infrarrojo.h>
// ES IMPORTANTE TENER LA LIBRERIA INFRARROJO.H para el manejo de los sensores IR


/*

Automatizacion - los tanques de combustible
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

/* MATERIALES
1 ARDUINO
2 SENSOR IR
1 LED
*/

/*CABLES para poder montarlo en una PROTOBOARD
Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA
 
 #cables | #hilos 
    2    |   3    M-M para conectar sensores IR
    1    |   1    M-M para conectar led indicador
    1    |   2    M-M para conectar tierra y corriente
 
*/ 
 
 ///////////////// SENSOR IR /////////////////
 
 
infrarrojo estado(7); // Definir PIN a usar para sensor IR 
infrarrojo estado2(8); // Definir PIN a usar para segundo sensor IR 
 
int VALOR; //valor para lectura del primer sensor IR
int VALOR2; //valor para lectura del segundo sensor IR
int led = 6;// MENSAJE EN ESTADO = 1 que se enviara a la central principal
int led_estado; // variable para sensor
int led_estado2;// varible para sensor


void setup() {
pinMode(led,OUTPUT);//LED QUE INDICA EL ESTADO DEL LED, SI SE REALIZO CON EXITO
Serial.begin(9600); //VELOCIDAD COMUNICACION SERIAL
}
//CODIGO PRINCIPAL
void loop() {
//Serial.print("\n leyendo estado sensor: \n");//IMPRIME MENSAJE EN PC
Serial.print(estado.lectura(VALOR));//IMPRIME EL ESTADO DEL Vo DEL SENSOR MEDIANTE LA VARIABLE VALOR
Serial.print(estado2.lectura(VALOR2));  // Vo segundo sensor

led_estado = estado.lectura(VALOR); // lectura del sensor IR
led_estado2 = estado.lectura(VALOR2); // lectura del segundo sensor IR


// LECTURA PARA SENSOR IR

if((led_estado == 0) && (led_estado2 == 0))// COMPARACION PARA ACTIVAR UN LED SEGUN EL ESTADO DEL SENSOR
{
  digitalWrite(led,HIGH); //<---
  // señal que se envia a la centrar principal
}
else 
{
  digitalWrite(led,LOW);
}


}

  

