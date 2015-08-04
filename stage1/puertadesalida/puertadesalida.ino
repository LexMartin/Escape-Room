#include <Servo.h>


/*

Automatizacion - puerta de salida
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int puntoUno = 2;
int puntoDos = 3;
int puntoTres = 4;
int puntoCuatro = 5;

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int puntoUno1 = 6;
int puntoDos2 = 7;
int puntoTres3 = 8;
int puntoCuatro4 = 9;

// validacion del juego
int correct = 13;  
int incorrect = 10;  


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


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  //entradas
  
  pinMode(puntoUno, INPUT); 
  pinMode(puntoDos, INPUT); 
  pinMode(puntoTres, INPUT); 
  pinMode(puntoCuatro, INPUT); 
  
  pinMode(puntoUno1, INPUT); 
  pinMode(puntoDos2, INPUT); 
  pinMode(puntoTres3, INPUT); 
  pinMode(puntoCuatro4, INPUT); 
  

  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
  
 
  
}

void loop() {
  
  
  temp1 = digitalRead(puntoUno);           temp5 = digitalRead(puntoUno1);  
  temp2 = digitalRead(puntoDos);           temp6 = digitalRead(puntoDos2);  
  temp3 = digitalRead(puntoTres);           temp7 = digitalRead(puntoTres3); 
   temp4 = digitalRead(puntoCuatro);           temp8 = digitalRead(puntoCuatro4);  
 

  
if( (comparePairs(puntoUno,puntoUno1)) && (comparePairs(puntoDos,puntoDos2)) && (comparePairs(puntoTres,puntoTres3)) && (comparePairs(puntoCuatro,puntoCuatro4)))
  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  temp = correct;
  temp = true;
  /*
  if(temp)
  {
    digitalWrite(z,HIGH);

  }
  */
  
  }
  else{
  digitalWrite(correct, LOW);
  digitalWrite(incorrect, HIGH);
  temp = correct;
  temp = false;
 
  
  
  }
  //Serial.println(comparePairs(ValTotem,OtherValTotem));
  
  
  
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
  
