

/*

Automatizacion - sarcofago
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
2 ARDUINOS
12 SENSORES HALL
2 LEDS
2 SOLENOIDE CERRADURA
2 CIRCUITOS MOSFET

*/


/*  CABLES para montar en PROTOBOARD
Cables para UN solo sarcofago, usar dos veces la lista para el segundo.


Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA



#CABLES | #HILOS | 
  2          2      M-M para corriente y tierra del protoboard, puente de protoboard
  6          3      M-H para sensores hall
  2          1      M-M para leds
  1          3      M-H para mosfet
  1          2      M-M para solenoide (no olvide los cables
                  para la conectarlo con la fuente de 12v)
  

  
*/





// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.




int placaColorAmarillo = 2; 
int placaColorNaranja = 3;
int placaColorRojo = 4;

// Estas son por seguridad, en caso de que las primeras partes no funcionen


int placaColorAmarillo1 = 5; 
int placaColorNaranja2 = 6;
int placaColorRojo3 = 7;

// validacion del juego

int correct = 13;  // llaves correctas
int incorrect = 8;

int mosfet = 11;

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

  //entrdas 
 pinMode(placaColorAmarillo, INPUT); 
 pinMode(placaColorNaranja, INPUT); 
 pinMode(placaColorRojo, INPUT); 
 
 pinMode(placaColorAmarillo1, INPUT); 
 pinMode(placaColorNaranja2, INPUT); 
 pinMode(placaColorRojo3, INPUT); 
 
 //salida
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 

  pinMode(mosfet, OUTPUT); 
  
  
  Serial.begin(9600); 
  
  
  
}



void loop() {
  
  
   
  temp1 = digitalRead(placaColorAmarillo);         temp4 = digitalRead(placaColorAmarillo1);  
  temp2 = digitalRead(placaColorNaranja);          temp5 = digitalRead(placaColorNaranja2);  
  temp3 = digitalRead(placaColorRojo);             temp6 = digitalRead(placaColorRojo3);  
 
  
 
  
  if(comparePairs(placaColorAmarillo,placaColorAmarillo1) && comparePairs(placaColorNaranja,placaColorNaranja2) && comparePairs(placaColorRojo,placaColorRojo3) ){
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  digitalWrite(mosfet, HIGH);

  }
  else{
  digitalWrite(incorrect, HIGH);
  digitalWrite(correct, LOW);
  digitalWrite(mosfet, LOW);

  }
 
  
} //loop



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
  

