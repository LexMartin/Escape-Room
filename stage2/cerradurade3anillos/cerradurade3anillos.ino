#include <Wire.h>
#include <pca9555.h>
// necessarios para GPIO


/*

Automatizacion - cerradura de tres anillos
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

/* MATERIALES
1 ARDUINO
2 GPIO
2 LED
1 RELAY o CIRCUITO MOSFET
20 SENSORES HALL
*/

/*CABLES para poder montarlo en una PROTOBOARD
Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA
 
 #cables | #hilos 
   20    |   3    H-H para conectar sensores hall
    1    |   4    H-H para conectar entre GPIO
    1    |   2    M-M para conectar tierra y corriente
    1    |   4    M-H para conectar GPIO con arduino
    2    |   2    H-H para conectar LEDs
 
*/ 

// GPIOs
pca9555 gpio1(0x20);
pca9555 gpio2(0x25);



int* entradasPin = new int [23];

// salida para el mosfet o relay en arduino
int mosfetForSolenoide = 3;

int temp = 0;
void setup() {
  
    pinMode(mosfetForSolenoide, OUTPUT);  
    
    Serial.begin(38400);
    delay(100);
    gpio1.begin();
    gpio2.begin();
    
    
    
  // entradas
   gpio1.gpioPinMode(INPUT);
  
  
   for(int i=0;i<=15;i++){
     if(i < 4){
       gpio2.gpioPinMode(i,INPUT);
     
     
     }else if(i>=4 && i<6){
      gpio2.gpioPinMode(i,OUTPUT);     
     
     }
   
   
   }
  

  Serial.begin(9600); 
}


void loop() {
      
   Serial.println(compararTodo());
   
   
   if(compararTodo()){
     gpio2.gpioDigitalWrite(4,HIGH);
     gpio2.gpioDigitalWrite(5,LOW);
     digitalWrite(mosfetForSolenoide, HIGH); 
   }else{
     
     gpio2.gpioDigitalWrite(4,LOW);
     gpio2.gpioDigitalWrite(5,HIGH);
     
     digitalWrite(mosfetForSolenoide, LOW);
   }
  
  

}
 
 // THIS FUNCTION IS FOR HALL SENSOR
bool getHallValue(int x){
    if(x < 16){
      if(gpio1.gpioDigitalRead(x)) return true;
      else return false; 
    }
    else if(x >= 16 && x < 32)
    {
      if(gpio2.gpioDigitalRead(x-16)) return true;
      else return false; 
    }
   
  }
  
  bool compararTodo()
  {
    
    bool variable = false;
    int foo = 0;
    int a,b;
    for(int i=1;i<=20;i=i+2){
   
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
  





  
