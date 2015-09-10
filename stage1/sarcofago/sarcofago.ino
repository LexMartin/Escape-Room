#include <Servo.h>

/*

Automatizacion - sarcofago
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
2 ARDUINOS
12 SENSORES HALL
2 LEDS
2 SERVOMOTORES
2 CIRCUITOS MOSFET

*/


/* CABLES
#CABLES | #HILOS | 
  12        3      para sensores hall (la parte A0 no se usa por eso son tres hilos por cable)
  2         2      para los leds
  2         3      para los circuitos mosfet



*Corriente y tierra del arduino dependende de como lo vayan ustedes a conectar 
*El servo motor necesita cables para una fuente de poder


*/





// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.




int placaColorAmarillo = 2; 
int placaColorNaranja = 3;
int placaColorRojo = 4;

// Estas son por seguridad, en caso de que las primeras partes no funcionen


int placaColorAmarillo1 = 5; 
int placaColorNaranja2 = 6;
int placaColorRojo3 = 7;

// validacion del juego

int correct = 13;  // llaves correctas
int incorrect = 8;


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


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {

  //entrdas 
 pinMode(placaColorAmarillo, INPUT); 
 pinMode(placaColorNaranja, INPUT); 
 pinMode(placaColorRojo, INPUT); 
 
 pinMode(placaColorAmarillo1, INPUT); 
 pinMode(placaColorNaranja2, INPUT); 
 pinMode(placaColorRojo3, INPUT); 
 
 //salida
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  //pinMode(servoActivo, OUTPUT);  
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
  
  
  
}



void loop() {
  
  
   
  temp1 = digitalRead(placaColorAmarillo);         temp4 = digitalRead(placaColorAmarillo1);  
  temp2 = digitalRead(placaColorNaranja);          temp5 = digitalRead(placaColorNaranja2);  
  temp3 = digitalRead(placaColorRojo);             temp6 = digitalRead(placaColorRojo3);  
 
  
 
  
  if(comparePairs(placaColorAmarillo,placaColorAmarillo1) && comparePairs(placaColorNaranja,placaColorNaranja2) && comparePairs(placaColorRojo,placaColorRojo3) ){
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  //temp = correct;
  temp = true;
  }
  else{
  digitalWrite(incorrect, HIGH);
  digitalWrite(correct, LOW);
  //temp = correct;
  temp = false;
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
 
 
  
} //loop



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
  

