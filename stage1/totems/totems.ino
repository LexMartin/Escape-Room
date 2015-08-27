#include <Servo.h>

/*

Automatizacion - totems
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
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
int correct = 13;  // Cuando las tres partes del totem estan correctas
int incorrect = 8; // el juego es incorrecto



// para servomotror
Servo servo; // se crea un objeto servo
int posicion = 0; // posicion del servo
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
  pinMode(totemPartOne, INPUT); 
  pinMode(totemPartTwo, INPUT); 
  pinMode(totemPartThree, INPUT); 
  
  pinMode(totemPart1, INPUT); 
  pinMode(totemPart2, INPUT); 
  pinMode(totemPart3, INPUT); 
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  //pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(9); // seleccionamos el PIN a usar.
  
  
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
  
  

  
  
  
  

