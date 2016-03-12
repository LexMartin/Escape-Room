#include <Wire.h>
#include <pca9555.h>





/*
Automatizacion - libros
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

/* MATERIALES
1 ARDUINO UNO
36 SENSORES HALL
3 GPIO
1 SOLENOIDE CERRADURA
2 LEDS
1 RELAY
*/

/*  CABLES para montar en PROTOBOARD

Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA


#CABLES | #HILOS | 
  36        3       H-H para sensores hall
  1         4       M-H para el primer GPIO - Arduino
  2         4       H-H para el segundo y tercer GPIO
  2         2       H-M  para leds
  1         3       uno M-H y dos H-H para el relay
  

*jumpers pequeños para gpio ya incluidos
*/

pca9555 gpio1(0x20);
pca9555 gpio2(0x25);
//ca9555 gpio3(0x27);

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.

int* entradasPin = new int [31];
int relay = 3;
int correctoLed = 4;
int incorrectoLed = 5;

// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN
int temp = 0;
void setup() {
  
    pinMode(relay, OUTPUT);  
    
    Serial.begin(38400);
    delay(100);
    gpio1.begin();//x.begin(true) will override automatic SPI initialization
    gpio2.begin();
  //  gpio3.begin();
    
    
    
  // entradas
   gpio1.gpioPinMode(INPUT);
   gpio2.gpioPinMode(INPUT);

  //salidas

  pinMode(relay, OUTPUT);  
  pinMode(correctoLed, OUTPUT);  
  pinMode(incorrectoLed, OUTPUT);  

   
   //gpio3.gpioPinMode(INPUT);
  
//   for(int i=0;i<=15;i++){
//     if(i < 4){
//       gpio3.gpioPinMode(i,INPUT);
//     
//     
//     }else if(i>=4 && i<6){
//      gpio3.gpioPinMode(i,OUTPUT);     
//     
//     }
//   
//   
//   }
  

  Serial.begin(9600); 
  

}

 
void loop() {
       
   //Serial.println("incio del LOOP");
   Serial.println(compararTodo());
   if(compararTodo()){
     digitalWrite(correctoLed,HIGH);
     digitalWrite(incorrectoLed,LOW);
     digitalWrite(relay, HIGH);
     //temp = true;
     
   
   
   }else{
     
     digitalWrite(correctoLed,LOW);
     digitalWrite(incorrectoLed,HIGH);
      //temp = false;
     digitalWrite(relay, LOW);
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
    for(int i=1;i<=31;i=i+2){
   
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
  
  

  
  
  
  

