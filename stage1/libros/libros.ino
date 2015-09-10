
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
  6         2 jumpers pequeños
  1         2        para leds
  
*Corriente y tierra del arduino dependende de como lo vayan ustedes a conectar 
*El servo motor necesita cables para una fuente de poder
  
*/

pca9555 gpio1(0x20);
pca9555 gpio2(0x25);
pca9555 gpio3(0x27);

// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

//int entradasPin[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}
//int entradasPin1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}

int* entradasPin = new int [35];

int correcto = 3;
int incorrecto = 4;

// para servomotror
Servo servo; // se crea un objeto servo
int posicion = 0; // posicion del servo
//int servoActivo = 9;
int temp = 0;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN
void setup() {
  // entradas
  for(int i=0;i<=35;i++){
    if(i<16){
      gpio1.gpioPinMode(i,INPUT);
    }else if(i>15 && i<32){
    
      gpio2.gpioPinMode(i-16,INPUT);
    }else if(i>31){
      gpio3.gpioPinMode(i-32,INPUT);
    }
  
  // salidas
  pinMode(correcto,OUTPUT);
  pinMode(incorrecto,OUTPUT);
  //pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(4); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
}
}

 
void loop() {

   if(compararTodo()){
     digitalWrite(correcto,HIGH);
     digitalWrite(incorrecto,LOW);
     temp = true;
     
   
   
   }else{
     digitalWrite(correcto,LOW);
     digitalWrite(incorrecto,HIGH);
     temp = false;
   }
  
  
  
  
  // activacion del servo
    if(temp)
  {
   // digitalWrite(servoActivo,HIGH);
    //posicion = 150;            // Establecemos el valor de la posicion a 150º  
    //posicion = map(posicion, 0, 1023, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM  
    servo.write(90);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else{
   //digitalWrite(servoActivo,LOW);
    servo.write(0);
  }
  
  
  
}
 
 
 // THIS FUNCTION IS FOR HALL SENSOR
bool getHallValue(int x){
    if(x < 16){
      if(gpio1.gpioDigitalRead(x)) return true;
      else return false; 
    }
    else if(x > 16 && x < 32)
    {
      if(gpio2.gpioDigitalRead(x-16)) return true;
      else return false; 
    }
    else if(x > 32)
    {
      if(gpio3.gpioDigitalRead(x-32)) return true;
      else return false;
    }
    
  }
  
  bool compararTodo()
  {
    bool variable = false;
    for(int i=1;i<=35;i+2){
      if (getHallValue(i) || getHallValue(i-1)){
        variable = true;
      
      }else{
        
        variable = false;
        break;
      }
    
    
    
    }
    
    return variable;
   
  }
  
  

  
  
  
  

