#include <Servo.h>

/*
Automatizacion - Calendario maya
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
1 ARDUINO UNO
1 SERVOMOTOR
1 CIRCUITO MOSFET
2 LEDS
6 SENSORES HALL
*/

/*  CABLES
#CABLES | #HILOS | 
  1          3     para circuito mosfet
  1          2     para los leds
  6          3     para sensores hall (la parte A0 no se usa por eso son tres hilos por cable)
  
  
*Corriente y tierra del arduino dependende de como lo vayan ustedes a conectar 
*El servo motor necesita cables para una fuente de poder
  
*/





// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int primerAnillo = 2; // primer anillo
int segundoAnillo = 3; // segungo anillo
int tercerAnillo = 4;

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int primerAnillo1 = 5;
int segundoAnillo2 = 6;
int tercerAnillo3 = 7;

//validacion del juego
int correct = 13;
int incorrect = 8;



// para servomotror
Servo servo; // se crea un objeto servo
int posicion=0; // posicion del servo
//int servoActivo = 9;


// variables para guardar
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
int temp6 = 0;

int temp = 0;

int mosfet = 11;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  
  //entradas
  pinMode(primerAnillo, INPUT);
  pinMode(segundoAnillo, INPUT);
  pinMode(tercerAnillo, INPUT);
  
  pinMode(primerAnillo1, INPUT);
  pinMode(segundoAnillo2, INPUT);
  pinMode(tercerAnillo3, INPUT);
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  
  pinMode(mosfet, OUTPUT); 
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temp1 = digitalRead(primerAnillo);   
  temp2 = digitalRead(segundoAnillo);

  
  temp3 = digitalRead(tercerAnillo); 
  temp4 = digitalRead(primerAnillo1);   
 
  temp5 = digitalRead(segundoAnillo2);  
  temp6 = digitalRead(tercerAnillo3); 
  
  
  
  if(comparePairs(primerAnillo,primerAnillo1) && comparePairs(segundoAnillo,segundoAnillo2) && comparePairs(tercerAnillo,tercerAnillo3) ){
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  //temp = correct;
  //temp = true;
  digitalWrite(mosfet, HIGH);
  }
  else{
  digitalWrite(incorrect, HIGH);
  digitalWrite(correct, LOW);
  //temp = correct;
  //temp = false;
  digitalWrite(mosfet, LOW);
  
  }
  
   // activacion del servo
    if(temp)
  {
    //digitalWrite(servoActivo,HIGH);
    //posicion = 150;            // Establecemos el valor de la posicion a 150º  
    //posicion = map(posicion, 0, 1023, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM  
    servo.write(90);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else{
   //digitalWrite(servoActivo,LOW);
    servo.write(0);  
  }
  
  
  
  
} // loop


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
  
  
  
