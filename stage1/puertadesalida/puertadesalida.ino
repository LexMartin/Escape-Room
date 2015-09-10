#include <Servo.h>


/*

Automatizacion - puerta de salida
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
8 FOTORESISTENCIAS 
1 ARDUINO UNO
1 SERVOMOTOR
1 CIRCUITO MOSFET
2 LEDS
*/

/*  CABLES
#CABLES | #HILOS | 
  8          3     para fotoresistencias
  1          3     para circuito mosfet
  2          2     para los leds
  
  
*Corriente y tierra del arduino dependende de como lo vayan ustedes a conectar 
*El servo motor necesita cables para una fuente de poder
  
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
int posicion=0; // posicion del servo
//int servoActivo = 9;

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
  //pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(11); // PIN PARA EL SERVOMOTOR
  
  
  Serial.begin(9600); 
  
 
  
}

void loop() {
  
  
  temp1 = digitalRead(puntoUno);          
  temp2 = digitalRead(puntoDos);       
  temp3 = digitalRead(puntoTres);         
   temp4 = digitalRead(puntoCuatro);      
 
/*
 temp5 = digitalRead(puntoUno1);  
      temp6 = digitalRead(puntoDos2);  
        temp7 = digitalRead(puntoTres3); 
             temp8 = digitalRead(puntoCuatro4);  */

// Descomentar la linea siguiente si el juego requiere que los 4 puntos tengan un respaldo, necesitara usar 8 fotoresistencias 
// el IF compara por medio de un or para asegurarse 
if( (comparePairs(puntoUno,puntoUno1)) && (comparePairs(puntoDos,puntoDos2)) && (comparePairs(puntoTres,puntoTres3)) && (comparePairs(puntoCuatro,puntoCuatro4))){
  
  
// en esta caso el juego solo tiene 4 fotoresistencias que son los 4 puntos de la puerta de salida  
 // if( getHallValue(puntoUno) && getHallValue(puntoDos) && getHallValue(puntoTres) && getHallValue(puntoCuatro))  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  //temp = correct;
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
  //temp = correct;
  temp = false;
 
  
  
  }
  //Serial.println(comparePairs(ValTotem,OtherValTotem));
  
  
  
  // activacion del servo
    if(temp)
  {
    //digitalWrite(servoActivo,HIGH);
    //posicion = 150;            // Establecemos el valor de la posicion a 150º  
    //posicion = map(posicion, 0, 1023, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM  
    servo.write(90);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else{
  // digitalWrite(servoActivo,LOW);
    servo.write(0);  
  }
  
  
  
 }  //loop
 
 
 // para las fotoresistencias
  bool getHallValue(int x){
    if (digitalRead(x)) return false;
    else return true;
  }
  
  bool comparePairs(int x, int y)
  {
    if(getHallValue(x) == true || getHallValue(y) == true ) 
    return true;
    else 
    return false;
  }
  
