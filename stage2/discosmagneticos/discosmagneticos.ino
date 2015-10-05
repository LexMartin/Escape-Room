#include <Servo.h>

/*

Automatizacion - discos magneticos
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/
/*
GPIO
16 SENSORES HALL
1 SOLENOIDE
1 MOSFET


*/

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int puntoUno = 3;
int puntoDos = 4;
int puntoTres = 5;
int puntoCuatro = 6;
int puntoCinco = 7;
int puntoSeis = 8;
int puntoSiete = 9;
int puntoOcho = 10;

// Estas son por seguridad, en caso de que las primeras partes no funcionen
int puntoUno1 = 11;
int puntoDos2 = 12;
int puntoTres3 = 13;
int puntoCuatro4 = 14;
int puntoCinco5 = 15;
int puntoSeis6 = 16;
int puntoSiete7 = 17;
int puntoOcho8 = 18;

// validacion del juego
int correct = 19;  // Cuando las tres partes del totem estan correctas
int incorrect = 20; // el juego es incorrecto


// para servomotror
Servo servo; // se crea un objeto servo
int posicion =0; // posicion del servo
//int servoActivo = 21;

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
int temp10 = 0;
int temp11 = 0;
int temp12 = 0;
int temp13 = 0;
int temp14 = 0;
int temp15 = 0;
int temp16 = 0;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  // entrada

  pinMode(puntoUno, INPUT); 
  pinMode(puntoDos, INPUT); 
  pinMode(puntoTres, INPUT); 
  pinMode(puntoCuatro, INPUT); 
  pinMode(puntoCinco, INPUT); 
  pinMode(puntoSeis, INPUT); 
  pinMode(puntoSiete, INPUT); 
  pinMode(puntoOcho, INPUT); 
  
  pinMode(puntoUno1, INPUT); 
  pinMode(puntoDos2, INPUT); 
  pinMode(puntoTres3, INPUT); 
  pinMode(puntoCuatro4, INPUT); 
  pinMode(puntoCinco5, INPUT); 
  pinMode(puntoSeis6, INPUT); 
  pinMode(puntoSiete7, INPUT); 
  pinMode(puntoOcho8, INPUT);
 
  //salida
  
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT);  
  pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
}

void loop() {
  temp1 = digitalRead(puntoUno); 
  temp2 = digitalRead(puntoDos); 
  temp3 = digitalRead(puntoTres); 
  temp4 = digitalRead(puntoCuatro); 
  temp5 = digitalRead(puntoCinco); 
  temp6 = digitalRead(puntoSeis); 
  temp7 = digitalRead(puntoSiete); 
  temp8 = digitalRead(puntoOcho); 
  
  temp9 = digitalRead(puntoUno1); 
  temp10 = digitalRead(puntoDos2); 
  temp11 = digitalRead(puntoTres3); 
  temp12 = digitalRead(puntoCuatro4); 
  temp13 = digitalRead(puntoCinco5); 
  temp14 = digitalRead(puntoSeis6); 
  temp15 = digitalRead(puntoSiete7); 
  temp16 = digitalRead(puntoOcho8); 
  
  if(comparePairs(puntoUno,puntoUno1) && comparePairs(puntoDos,puntoDos2) && comparePairs(puntoTres,puntoTres3) && comparePairs(puntoCuatro,puntoCuatro4) 
  && comparePairs(puntoCinco,puntoCinco5) && comparePairs(puntoSeis,puntoSeis6) && comparePairs(puntoSiete,puntoSiete7) && comparePairs(puntoOcho,puntoOcho8)){
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
