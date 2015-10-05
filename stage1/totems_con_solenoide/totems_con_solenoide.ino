
/*

Automatizacion - totems
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
4 ARDUINO UNO
24 SENSORES HALL
3 CIRCUITO MOSFET
3 SOLENOIDES
10 LEDS
1 LASER
*/




/*  CABLES para montar en PROTOBOARD
CASO DE TOTEM CON SOLENOIDE, cables para solo UN TOTEM
Seria tres veces para los TRES TOTEMS

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




int totemPartOne = 3; // Parte uno del totem
int totemPartTwo = 4; // parte dos
int totemPartThree = 5; // parte tres

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int totemPart1 = 6; // respaldo de parte uno del totem
int totemPart2  = 7; // respaldo parte dos
int totemPart3 = 8;  // respaldo parte tres

// validacion del juego
int correct = 9;  // Cuando las tres partes del totem estan correctas
int incorrect = 10; // el juego es incorrecto






//variables para guardar
int temp = 0;
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
  // entradas
 
  
  pinMode(totemPartOne, INPUT); 
  pinMode(totemPartTwo, INPUT); 
  pinMode(totemPartThree, INPUT); 
  
  pinMode(totemPart1, INPUT); 
  pinMode(totemPart2, INPUT); 
 
 
  
 
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  pinMode(mosfet,OUTPUT);
  

  
  Serial.begin(9600); 
}

 
void loop() {
  

  temp1 = digitalRead(totemPartOne);           temp4 = digitalRead(totemPart1);  
  temp2 = digitalRead(totemPartTwo);           temp5 = digitalRead(totemPart2);  
  temp3 = digitalRead(totemPartThree);         temp6 = digitalRead(totemPart3);  
 
 
  if( (comparePairs(totemPartOne,totemPart1)) && (comparePairs(totemPartTwo,totemPart2)) && (comparePairs(totemPartThree,totemPart3)))
  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
   digitalWrite(mosfet, HIGH);
  }
  
  
  else{
  digitalWrite(correct, LOW);
  digitalWrite(incorrect, HIGH);
  digitalWrite(mosfet, LOW); 
  }
   
  
 }  //loop
 
 
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
  
 


