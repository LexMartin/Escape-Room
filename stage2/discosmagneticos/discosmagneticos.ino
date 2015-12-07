#include <Wire.h>
#include <pca9555.h>



/*

Automatizacion - discos magneticos
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


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
    gpio1.begin();//x.begin(true) will override automatic SPI initialization

    
    
    
  // entradas
   gpio1.gpioPinMode(INPUT);
  
  Serial.begin(9600); 
}

void loop() {
       
   //Serial.println("incio del LOOP");
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
  






