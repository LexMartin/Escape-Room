#include <Wire.h>
#include <pca9555.h>


/*

Automatizacion - cerradura de tres anillos
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

pca9555 gpio1(0x20);
pca9555 gpio2(0x25);

int* entradasPin = new int [23];
// 20 entradas
// 2 salidoas, correcto e incorrecto
// 1 salida para el mosfet
int mosfetForSolenoide = 3;

int temp = 0;
void setup() {
  
    pinMode(mosfetForSolenoide, OUTPUT);  
    
    Serial.begin(38400);
    delay(100);
    gpio1.begin();//x.begin(true) will override automatic SPI initialization
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
       
   //Serial.println("incio del LOOP");
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
    for(int i=1;i<=35;i=i+2){
   
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
  





  
