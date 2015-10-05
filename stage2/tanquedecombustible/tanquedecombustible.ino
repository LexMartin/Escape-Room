#include <infrarrojo.h>

/*

Automatizacion - los tanques de combustible
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

 /*
///////////////// SENSOR HALL //////////////////
 
// Esta parte es en caso de usar sensores hall

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int bolaDeGolf = 3;
int bolaDeGolf1 = 4; // esta en caso de seguridad


// validacion del juego
int tanqueLleno = 13;
int tanqueNoLleno = 2;



// variables para guardar
int temp1 = 0;
int temp2 = 0;

// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  // entradas
  pinMode(bolaDeGolf, INPUT); 
  pinMode(bolaDeGolf1, INPUT); 

  // salidas
  pinMode(tanqueLleno, OUTPUT);  
  pinMode(tanqueNoLleno, OUTPUT);  

 
  
  Serial.begin(9600); 

}

void loop() {
  
    temp1 = digitalRead(bolaDeGolf);           temp2 = digitalRead(bolaDeGolf1);  
 
  if(comparePairs(bolaDeGolf,bolaDeGolf1)){
  digitalWrite(tanqueLleno, HIGH);
  digitalWrite(tanqueNoLleno, LOW);
  
  }
  else{
  digitalWrite(tanqueNoLleno, HIGH);
  digitalWrite(tanqueLleno, LOW);

  
  }
  
  
  
}// loop

  
 // THIS FUNCTION IS FOR HALL SENSOR
  bool getHallValue(int x){
    if (digitalRead(x)) return true;
    else return false;
  }
  
  bool comparePairs(int x, int y)
  {
    if(getHallValue(x) == true || getHallValue(y) == true ) 
    return true;
    else 
    return false;
  }
  
  
 */
 
 
 /*
 1 sensor IR 
 
 
 
 
 */
 
 
 
 ///////////////// SENSOR IR /////////////////
 
 
 infrarrojo estado(13);//DEFINICION DEL PIN DEL ARDUINO A USAR
int VALOR;//VARIBLE QUE RECIBE EL DATO
int led =12;//REDEFINICION DE PIN DE ARDUINO PARA LED INDICADOR DE PULSO(ESTO ES OPCIONAL)
int led_estado;//VARIABLE


void setup() {
pinMode(led,OUTPUT);//LED QUE INDICA EL ESTADO DEL LED
Serial.begin(9600); //VELOCIDAD COMUNICACION SERIAL
}
//CODIGO PRINCIPAL
void loop() {
Serial.print("\n leyendo estado sensor: \n");//IMPRIME MENSAJE EN PC
Serial.print(estado.lectura(VALOR));//IMPRIME EL ESTADO DEL Vo DEL SENSOR MEDIANTE LA VARIABLE VALOR
led_estado = estado.lectura(VALOR);//LED QUE RECOGE EL ESTADO DEL SENSOR
if(led_estado == 1)// COMPARACION PARA ACTIVAR UN LED SEGUN EL ESTADO DEL SENSOR
{
  digitalWrite(led,HIGH);
}
else
{
  digitalWrite(led,LOW);
}
delay(100);

}

  

