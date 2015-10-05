
/*
Automatizacion - Calendario maya
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
1 ARDUINO UNO
1 SOLENOIDE CERRADURA
1 RELAY
2 LEDS
6 SENSORES HALL
*/


/*  CABLES para montar en PROTOBOARD

Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA



#CABLES | #HILOS | 
  2          2      M-M para corriente y tierra del protoboard, puente de protoboard
  6          3      M-H para sensores hall
  2          1      M-M para leds
  1          3      M-H para relay
  1          2      M-M para solenoide (no olvide los cables
                  para la conectarlo con la fuente de 12v)
  

  
*/





// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int primerAnillo = 2; // primer anillo
int segundoAnillo = 3; // segungo anillo
int tercerAnillo = 4;

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int primerAnillo1 = 5;
int segundoAnillo2 = 6;
int tercerAnillo3 = 7;

//validacion del juego
int correct = 13;
int incorrect = 8;


// variables para guardar
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
int temp6 = 0;



int mosfet = 11;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  
  //entradas
  pinMode(primerAnillo, INPUT);
  pinMode(segundoAnillo, INPUT);
  pinMode(tercerAnillo, INPUT);
  
  pinMode(primerAnillo1, INPUT);
  pinMode(segundoAnillo2, INPUT);
  pinMode(tercerAnillo3, INPUT);
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  
  pinMode(mosfet, OUTPUT); 
  

  
  
  Serial.begin(9600); 
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temp1 = digitalRead(primerAnillo);   
  temp2 = digitalRead(segundoAnillo);

  
  temp3 = digitalRead(tercerAnillo); 
  temp4 = digitalRead(primerAnillo1);   
 
  temp5 = digitalRead(segundoAnillo2);  
  temp6 = digitalRead(tercerAnillo3); 
  
  
  
  if(comparePairs(primerAnillo,primerAnillo1) && comparePairs(segundoAnillo,segundoAnillo2) && comparePairs(tercerAnillo,tercerAnillo3) ){
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  digitalWrite(mosfet, HIGH);
  }
  else{
  digitalWrite(incorrect, HIGH);
  digitalWrite(correct, LOW);
  digitalWrite(mosfet, LOW);
  
  }
 
  
} // loop


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
  
  
  
