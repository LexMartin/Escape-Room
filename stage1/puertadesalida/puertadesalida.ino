
/*

Automatizacion - puerta de salida
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


/* MATERIALES
8 FOTORESISTENCIAS 
1 ARDUINO UNO
1 SOLENOIDE
1 Relay
2 LEDS
*/

/*  CABLES para montar en PROTOBOARD



Jumpers:
M-M: MACHO A MACHO
M-H: MACHO A HEMBRA
H-H: HEMBRA A HEMBRA



#CABLES | #HILOS | 
  2          2      M-M para corriente y tierra del protoboard, puente de protoboard
  8          3       M-H para fotoresistencias
  2          1      M-M para leds
  1          3      M-H para relay
  1          2      M-M para solenoide (no olvide los cables
                  para la conectarlo con la fuente de 12v)
  
  

  
*/


// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int puntoUno = 2;
int puntoDos = 3;
int puntoTres = 4;
int puntoCuatro = 5;

// Estas son por seguridad, en caso de que las primeras partes no funcionen


int puntoUno1 = 6;
int puntoDos2 = 7;
int puntoTres3 = 8;
int puntoCuatro4 = 9;


// validacion del juego
int correct = 13;  
int incorrect = 10;  

int mosfet = 12;


//variables para guardar
int temp = 0;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
int temp6 = 0;
int temp7 = 0;
int temp8 = 0;


// INPUTS AND OUTPUTS, entradas y salidas
// para declarar la entra o salida del PIN

void setup() {
  //entradas
  
  pinMode(puntoUno, INPUT); 
  pinMode(puntoDos, INPUT); 
  pinMode(puntoTres, INPUT); 
  pinMode(puntoCuatro, INPUT); 
  
  
  pinMode(puntoUno1, INPUT); 
  pinMode(puntoDos2, INPUT); 
  pinMode(puntoTres3, INPUT); 
  pinMode(puntoCuatro4, INPUT); 
  pinMode(mosfet,OUTPUT);

  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
    
 
  Serial.begin(9600); 
  
 
  
}

void loop() {
  
  
  temp1 = digitalRead(puntoUno);          
  temp2 = digitalRead(puntoDos);       
  temp3 = digitalRead(puntoTres);         
   temp4 = digitalRead(puntoCuatro);      
 

 temp5 = digitalRead(puntoUno1);  
 temp6 = digitalRead(puntoDos2);  
  temp7 = digitalRead(puntoTres3); 
   temp8 = digitalRead(puntoCuatro4);  

// Descomentar la linea siguiente si el juego requiere que los 4 puntos tengan un respaldo, necesitara usar 8 fotoresistencias 
// el IF compara por medio de un or para asegurarse 
if( (comparePairs(puntoUno,puntoUno1)) && (comparePairs(puntoDos,puntoDos2)) && (comparePairs(puntoTres,puntoTres3)) && (comparePairs(puntoCuatro,puntoCuatro4))){
  
  
// en esta caso el juego solo tiene 4 fotoresistencias que son los 4 puntos de la puerta de salida  
 // if( getHallValue(puntoUno) && getHallValue(puntoDos) && getHallValue(puntoTres) && getHallValue(puntoCuatro))  {
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
 
 
 // para las fotoresistencias
  bool getHallValue(int x){
    if (!digitalRead(x)) return false;
    else return true;
  }
  
  bool comparePairs(int x, int y)
  {
    if(getHallValue(x) == true || getHallValue(y) == true ) 
    return true;
    else 
    return false;
  }
  
