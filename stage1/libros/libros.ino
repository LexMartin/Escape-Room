
#include <Wire.h>
#include <pca9555.h>

#include <Servo.h>

/*
Automatizacion - libros
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/

/* MATERIALES
1 ARDUINO UNO
36 SENSORES HALL
3 GPIO
1 CIRCUITO MOSFET
1 SOLENOIDE CERRADURA
2 LEDS
*/

/*  CABLES
#CABLES | #HILOS | 
  36        3       para sensores hall
  3         4       para GPIO
  1         3       para mosfet
  2         2        para leds
  
*Corriente y tierra del arduino dependende de como lo vayan ustedes a conectar 
*El solenoide necesita cables para una fuente de poder
*jumpers pequeños para gpio ya incluidos
*/

pca9555 gpio1(0x20);
pca9555 gpio2(0x25);
pca9555 gpio3(0x27);

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.

int* entradasPin = new int [35];


// para servomotror

Servo servo; // se crea un objeto servo
int posicion = 0; // posicion del servo
//int servoActivo = 9;
int temp = 0;

// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN
void setup() {
  
  
    
    Serial.begin(38400);
    delay(100);
    gpio1.begin();//x.begin(true) will override automatic SPI initialization
    gpio2.begin();
    gpio3.begin();
    
    
    
  // entradas
   gpio1.gpioPinMode(INPUT);
   gpio2.gpioPinMode(INPUT);
   //gpio3.gpioPinMode(INPUT);
  
   for(int i=0;i<=15;i++){
     if(i < 4){
       gpio3.gpioPinMode(i,INPUT);
     
     
     }else if(i>=4 && i<6){
      gpio3.gpioPinMode(i,OUTPUT);     
     
     }
   
   
   }
  
   
  
  // servomotor
   servo.attach(3); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
  

}

 
void loop() {

   //Serial.println("incio del LOOP");
   Serial.println(compararTodo());
   if(compararTodo()){
     gpio3.gpioDigitalWrite(4,HIGH);
     gpio3.gpioDigitalWrite(5,LOW);
    
     temp = true;
     
   
   
   }else{
     
     gpio3.gpioDigitalWrite(4,LOW);
     gpio3.gpioDigitalWrite(5,HIGH);
      temp = false;
   }
  
  

  
  // activacion del servo
    if(temp)
  {
    servo.write(90);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else{
    servo.write(0);
  }
  
  Serial.println("fin del lOOP");
  

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
    else if(x >= 32)
    {
      if(gpio3.gpioDigitalRead(x-32)) return true;
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
  
  

  
  
  
  

