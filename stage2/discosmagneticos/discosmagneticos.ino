#include <Wire.h>
#include <pca9555.h>


/*
Automatizacion - discos magneticos
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

/* MATERIALES
1 ARDUINO
1 GPIO
2 LED
1 RELAY o CIRCUITO MOSFET
16 SENSORES HALL
*/

/*CABLES para poder montarlo en una PROTOBOARD
Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA
 
 #cables | #hilos 
   16    |   3    H-H para conectar sensores hall
    1    |   2    M-M para conectar tierra y corriente
    1    |   4    M-H para conectar GPIO con arduino
    2    |   2    H-H para conectar LEDs
 
*/

// GPIO
pca9555 gpio1(0x20);

int* entradasPin = new int [16];

int mosfetForSolenoide = 3;
int correcto = 4;
int incorrecto = 5;

int temp = 0;
void setup() {
  
    pinMode(mosfetForSolenoide, OUTPUT);  
    pinMode(correcto, OUTPUT);  
    pinMode(incorrecto, OUTPUT);  
    
    Serial.begin(38400);
    delay(100);
    gpio1.begin();

    
    
    
  // entradas
   gpio1.gpioPinMode(INPUT);
  
  Serial.begin(9600); 
}

void loop() {
       
 
   Serial.println(compararTodo());
   if(compararTodo()){
   digitalWrite(correcto, HIGH);
   digitalWrite(incorrecto, LOW);  
   digitalWrite(mosfetForSolenoide, HIGH); 
   }else{
   digitalWrite(correcto, LOW);
   digitalWrite(incorrecto, HIGH);  
   digitalWrite(mosfetForSolenoide, LOW);
   }
  
  

}

 
 // THIS FUNCTION IS FOR HALL SENSOR
bool getHallValue(int x){
    if(x < 16){
      if(gpio1.gpioDigitalRead(x)) return true;
      else return false; 
    }
  }
  
  bool compararTodo()
  {
    
    bool variable = false;
    int foo = 0;
    int a,b;
    for(int i=1;i<=16;i=i+2){
   
      a =getHallValue(i);
      b=getHallValue(i-1);
    
      if (a || b){
        variable = true;
      }else{
        
        variable = false;
        foo++;
        break;
      }
    }
   
    
    return variable;
   
  }
  






