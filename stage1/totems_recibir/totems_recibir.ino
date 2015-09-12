#include <gpio_expander.h>
#include <Wire.h>
#include <pca9555.h>

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


pca9555 gpio1(0x20);

int totemPartOne = 2; // Parte uno del totem
int totemPartTwo = 3; // parte dos
int totemPartThree = 4; // parte tres

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int totemPart1 = 5; // respaldo de parte uno del totem
int totemPart2  = 6; // respaldo parte dos
int totemPart3 = 7;  // respaldo parte tres

// validacion del juego
int correct = 8; // Cuando las tres partes del totem estan correctas
int incorrect = 9; // el juego es incorrecto
int ojos1 = 10; 
int ojos2 = 11;

int laser = 12;

//variables para guardar
//int temp = 0;
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
   Serial.begin(38400);
   delay(100);
   gpio1.begin();
   
   
   for(int i=0;i<=15;i++){
    if(i < 3){
      gpio1.gpioPinMode(i,INPUT);
    }else if(i >= 3 && i< 6){
      gpio1.gpioPinMode(i,OUTPUT); 
    }   
    
   } 
  pinMode(totemPartOne, INPUT); 
  pinMode(totemPartTwo, INPUT); 
  pinMode(totemPartThree, INPUT); 
  
  pinMode(totemPart1, INPUT); 
  pinMode(totemPart2, INPUT); 
  pinMode(totemPart3, INPUT); 
 
  // salidas
  pinMode(correct, OUTPUT);
  pinMode(incorrect, OUTPUT); 
  
  pinMode(ojos1, OUTPUT);
  pinMode(ojos2, OUTPUT);
  
  pinMode(laser,OUTPUT);
}
  
void loop() {
  temp1 = digitalRead(totemPartOne);           temp4 = digitalRead(totemPart1);  
  temp2 = digitalRead(totemPartTwo);           temp5 = digitalRead(totemPart2);  
  temp3 = digitalRead(totemPartThree);         temp6 = digitalRead(totemPart3);  

  if( (comparePairs(totemPartOne,totemPart1)) && (comparePairs(totemPartTwo,totemPart2)) && (comparePairs(totemPartThree,totemPart3)))
  {
  digitalWrite(correct, HIGH);
  //digitalWrite(correct2, LOW);
  digitalWrite(incorrect, LOW);
  gpio1.gpioDigitalWrite(3,LOW);
  gpio1.gpioDigitalWrite(4,LOW);
  gpio1.gpioDigitalWrite(5,LOW);
  digitalWrite(ojos1, LOW);
  digitalWrite(ojos2, LOW);
  delay(5);
  digitalWrite(laser,LOW);
  
  
  
    if(obtenerGpioValor()){
      gpio1.gpioDigitalWrite(3,HIGH);
      gpio1.gpioDigitalWrite(4,HIGH);
      gpio1.gpioDigitalWrite(5,HIGH);
      delay(10000);
      
      digitalWrite(ojos1, HIGH);
       digitalWrite(ojos2, HIGH);
       delay(2000);
       digitalWrite(laser,HIGH);
    }
    else{
      gpio1.gpioDigitalWrite(3,LOW);
      gpio1.gpioDigitalWrite(4,LOW);
      gpio1.gpioDigitalWrite(5,LOW);
      digitalWrite(ojos1, LOW);
       digitalWrite(ojos2, LOW);
       digitalWrite(laser,LOW);
    }
  
  }
  
   else{
  digitalWrite(correct, LOW);
  //digitalWrite(correct2, LOW);
  digitalWrite(incorrect, HIGH);
  gpio1.gpioDigitalWrite(3,LOW);
     gpio1.gpioDigitalWrite(4,LOW);
     gpio1.gpioDigitalWrite(5,LOW);
  digitalWrite(ojos1, LOW);
  digitalWrite(ojos2, LOW);
       delay(5);
       digitalWrite(laser,LOW);
  
  }// else
  }
    
 
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
  
 
bool getHallValue2(int x)
 {
    if(x < 16){
      if(gpio1.gpioDigitalRead(x)) return true;
      else return false; 
    }else{
    return false;
    }
    
  }
  
  
   bool obtenerGpioValor()
  {
    for(int i=0; i<=2; i++){
      if(getHallValue2(i) == true && getHallValue2(i+1) == true && getHallValue2(i+2) == true) 
      return true;
      else 
      return false;
    
    
    }
    
    
    
    
  }

