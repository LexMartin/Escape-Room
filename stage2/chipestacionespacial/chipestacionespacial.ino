#include <Servo.h>

/*

Automatizacion - chip, estacion espacial
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/
/*
material
1 arduino
6 sensores hall
2 leds
1 solenoide cerradura
1 circuito mosfet

*/

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int llaveEscarabajoUno = 2; 
int llaveEscarabajoDos = 3; 
int llaveEscarabajoTres = 4; 

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int llaveEscarabajoUno1 = 5; 
int llaveEscarabajoDos2  = 6; 
int llaveEscarabajoTres3 = 7;  

// validacion del juego
int correct = 13;  
int incorrect = 8; 



// para servomotror
Servo servo; // se crea un objeto servo
int posicion =0; // posicion del servo
//int servoActivo = 9;

//variables para guardar
int temp = 0;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
int temp6 = 0;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN
void setup() {
  // entradas
  pinMode(llaveEscarabajoUno, INPUT); 
  pinMode(llaveEscarabajoDos, INPUT); 
  pinMode(llaveEscarabajoTres, INPUT); 
  
  pinMode(llaveEscarabajoUno1, INPUT); 
  pinMode(llaveEscarabajoDos2, INPUT); 
  pinMode(llaveEscarabajoTres3, INPUT); 
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
}

 
void loop() {
  
  temp1 = digitalRead(llaveEscarabajoUno);           temp4 = digitalRead(llaveEscarabajoUno1);  
  temp2 = digitalRead(llaveEscarabajoDos);           temp5 = digitalRead(llaveEscarabajoDos2);  
  temp3 = digitalRead(llaveEscarabajoTres);         temp6 = digitalRead(llaveEscarabajoTres3);  
 
 
  if( (comparePairs(llaveEscarabajoUno,llaveEscarabajoUno1)) && (comparePairs(llaveEscarabajoDos,llaveEscarabajoDos2)) && (comparePairs(llaveEscarabajoTres,llaveEscarabajoTres3)))
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
  
  

  
  
  
  

