#include <Servo.h>

/*
Automatizacion - Calendario maya
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int primerAnillo = 2; // primer anillo
int segundoAnillo = 3; // segungo anillo

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int primerAnillo1 = 4;
int segundoAnillo2 = 5;

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
int temp = 0;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  
  //entradas
  pinMode(primerAnillo, INPUT);
  pinMode(segundoAnillo, INPUT);
  
  
  pinMode(primerAnillo1, INPUT);
  pinMode(segundoAnillo2, INPUT);
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temp1 = digitalRead(primerAnillo);   
  temp2 = digitalRead(segundoAnillo);

  
  temp3 = digitalRead(primerAnillo1); 
  temp4 = digitalRead(segundoAnillo2);   
 
 
 
  
  if(comparePairs(primerAnillo,primerAnillo1) && comparePairs(segundoAnillo,segundoAnillo2) ){
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  temp = correct;
  temp = true;
 
  }
  else{
  digitalWrite(incorrect, HIGH);
  digitalWrite(correct, LOW);
  temp = correct;
  temp = false;
  
  }
  
   // activacion del servo
    if(temp == HIGH)
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
  
  
  
