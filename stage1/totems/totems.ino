#include <Servo.h>

/*

Automatizacion - totems
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

/* MATERIALES
4 ARDUINO UNO
24 SENSORES HALL
3 CIRCUITO MOSFET
3 SERVOS
9 LEDS
1 LASER
*/

/*  CABLES


#CABLES | #HILOS | 
  24        3      para sensores hall
  3         3      para circuito mosfet
  1         3      para el laser
  9         2      para los leds

  
*Corriente y tierra del arduino dependende de como lo vayan ustedes a conectar 
*El servo motor necesita cables para una fuente de poder
  
*/
// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.




int totemPartOne = 2; // Parte uno del totem
int totemPartTwo = 3; // parte dos
int totemPartThree = 4; // parte tres

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int totemPart1 = 5; // respaldo de parte uno del totem
int totemPart2  = 6; // respaldo parte dos
int totemPart3 = 7;  // respaldo parte tres

// validacion del juego
int correct = 8;  // Cuando las tres partes del totem estan correctas
int incorrect = 9; // el juego es incorrecto


//int servo;

// ENVIAR
const int arduinoUnoCorrecto = 10;

// RECIBIR
const int enviarArduinoCuatroCorrecto = 11;


int recibirEnviarArduinoCuatroUnoCorrecto; 


// para servomotror
Servo servo; // se crea un objeto servo
int posicion = 0; // posicion del servo
//int temp = 0;


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
 
  
  pinMode(totemPartOne, INPUT); 
  pinMode(totemPartTwo, INPUT); 
  pinMode(totemPartThree, INPUT); 
  
  pinMode(totemPart1, INPUT); 
  pinMode(totemPart2, INPUT); 
 
 
  
 
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
    
  
  // ENVIAR RECIBIR
  pinMode(enviarArduinoCuatroCorrecto, INPUT); 
  pinMode(arduinoUnoCorrecto, OUTPUT); 
  
  // servomotor
  servo.attach(12); // seleccionamos el PIN a usar.

  
  Serial.begin(9600); 
}

 
void loop() {
  

  temp1 = digitalRead(totemPartOne);           temp4 = digitalRead(totemPart1);  
  temp2 = digitalRead(totemPartTwo);           temp5 = digitalRead(totemPart2);  
  temp3 = digitalRead(totemPartThree);         temp6 = digitalRead(totemPart3);  
 
 
  if( (comparePairs(totemPartOne,totemPart1)) && (comparePairs(totemPartTwo,totemPart2)) && (comparePairs(totemPartThree,totemPart3)))
  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  digitalWrite(arduinoUnoCorrecto,HIGH);
  recibirEnviarArduinoCuatroUnoCorrecto = digitalRead(enviarArduinoCuatroCorrecto);
  if (recibirEnviarArduinoCuatroUnoCorrecto == HIGH){
      temp = true;
  }
  else if (recibirEnviarArduinoCuatroUnoCorrecto == LOW){
     temp = false;
  }  
  }
  else{
  digitalWrite(correct, LOW);
  digitalWrite(incorrect, HIGH);
  digitalWrite(arduinoUnoCorrecto,LOW);
  }
   
  // activacion del servo
    if(temp == HIGH)
  {
    delay(5000);
    servo.write(90);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else if(temp == LOW){
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
  
 


