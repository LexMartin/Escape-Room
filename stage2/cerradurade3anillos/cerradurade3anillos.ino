#include <Servo.h>

/*

Automatizacion - cerradura de tres anillos
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.


int primerAgujero = 3;
int segundoAgujero = 4;
int tercerAgujero = 5; 
int cuartoAgujero = 6; 
int quintoAgujero = 7;
int sextoAgujero = 8;
int septimoAgujero = 24;
int octavoAgujero = 10;
int novenoAgujero = 11;
int ceroAgujero = 12;

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int primerAgujero1 = 13;
int segundoAgujero2 = 14;
int tercerAgujero3 = 15;
int cuartoAgujero4 = 16;
int quintoAgujero5 = 17;
int sextoAgujero6 = 18;
int septimoAgujero7 = 19;
int octavoAgujero8 = 20;
int novenoAgujero9 = 21;
int ceroAgujero0 = 22;

// validacion del juego
int correct = 23;  
int incorrect = 2; 

// para servomotror
Servo servo; // se crea un objeto servo
int posicion; // posicion del servo
int servoActivo = 9;

//variables para guardar
int temp = 0;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
int temp6 = 0;
int temp7 = 0;
int temp8 = 0;
int temp9 = 0;
int temp0 = 0;

int temp11 = 0;
int temp22 = 0;
int temp33 = 0;
int temp44 = 0;
int temp55 = 0;
int temp66 = 0;
int temp77 = 0;
int temp88 = 0;
int temp99 = 0;
int temp00 = 0;



// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  // entrada
  pinMode(primerAgujero, INPUT); 
  pinMode(segundoAgujero, INPUT); 
  pinMode(tercerAgujero, INPUT); 
  pinMode(cuartoAgujero, INPUT); 
  pinMode(quintoAgujero, INPUT); 
  pinMode(sextoAgujero, INPUT); 
  pinMode(septimoAgujero, INPUT); 
  pinMode(octavoAgujero, INPUT); 
  pinMode(novenoAgujero, INPUT); 
  pinMode(ceroAgujero, INPUT); 
  
  pinMode(primerAgujero1, INPUT); 
  pinMode(segundoAgujero2, INPUT); 
  pinMode(tercerAgujero3, INPUT); 
  pinMode(cuartoAgujero4, INPUT); 
  pinMode(quintoAgujero5, INPUT); 
  pinMode(sextoAgujero6, INPUT); 
  pinMode(septimoAgujero7, INPUT); 
  pinMode(octavoAgujero8, INPUT); 
  pinMode(novenoAgujero9, INPUT); 
  pinMode(ceroAgujero0, INPUT); 
  
  
  
  // salida
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  pinMode(servoActivo, OUTPUT);  
  
  
    // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
  
}



void loop() {
  int temp1 = digitalRead(primerAgujero); 
  int temp2 = digitalRead(segundoAgujero); 
  int temp3 = digitalRead(tercerAgujero); 
  int temp4 = digitalRead(cuartoAgujero); 
  int temp5 = digitalRead(quintoAgujero); 
  int temp6 = digitalRead(sextoAgujero); 
  int temp7 = digitalRead(septimoAgujero); 
  int temp8 = digitalRead(octavoAgujero); 
  int temp9 = digitalRead(novenoAgujero); 
  int temp0 = digitalRead(ceroAgujero); 
  
  int temp11 = digitalRead(primerAgujero1); 
  int temp22 = digitalRead(segundoAgujero2); 
  int temp33 = digitalRead(tercerAgujero3); 
  int temp44 = digitalRead(cuartoAgujero4); 
  int temp55 = digitalRead(quintoAgujero5); 
  int temp66 = digitalRead(sextoAgujero6); 
  int temp77 = digitalRead(septimoAgujero7); 
  int temp88 = digitalRead(octavoAgujero8); 
  int temp99 = digitalRead(novenoAgujero9); 
  int temp00 = digitalRead(ceroAgujero0); 


  
  if(comparePairs(primerAgujero,primerAgujero1) && comparePairs(segundoAgujero,segundoAgujero2)
  && comparePairs(tercerAgujero,tercerAgujero3) && comparePairs(cuartoAgujero,cuartoAgujero4) 
  && comparePairs(quintoAgujero,quintoAgujero5) && comparePairs(sextoAgujero,sextoAgujero6) 
  && comparePairs(septimoAgujero,septimoAgujero7) && comparePairs(octavoAgujero,octavoAgujero8) 
  && comparePairs(novenoAgujero,novenoAgujero9) && comparePairs(ceroAgujero,ceroAgujero0)  )
  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  temp = correct;
  temp = true;
  }
  else{
  digitalWrite(correct, LOW);
  digitalWrite(incorrect, HIGH);
  temp = correct;
  temp = false;
  }
  // activacion del servo
    if(temp == HIGH)
  {
    digitalWrite(servoActivo,HIGH);
    posicion = 150;            // Establecemos el valor de la posicion a 150º  
    posicion = map(posicion, 0, 1023, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM  
    servo.write(posicion);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else{
   digitalWrite(servoActivo,LOW);
  
  }
 }  //loop

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
  
