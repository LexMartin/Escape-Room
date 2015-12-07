
/*

Automatizacion - chip, estacion espacial
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/





// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int llaveEscarabajoUno = 2; 
int llaveEscarabajoDos = 3; 
int llaveEscarabajoTres = 4; 

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int llaveEscarabajoUno1 = 5; 
int llaveEscarabajoDos2  = 6; 
int llaveEscarabajoTres3 = 7;  

// validacion del juego
int correct = 13;  
int incorrect = 8; 

int mosfetForSolenoide = 11;


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
  // entradas
  pinMode(llaveEscarabajoUno, INPUT); 
  pinMode(llaveEscarabajoDos, INPUT); 
  pinMode(llaveEscarabajoTres, INPUT); 
  
  pinMode(llaveEscarabajoUno1, INPUT); 
  pinMode(llaveEscarabajoDos2, INPUT); 
  pinMode(llaveEscarabajoTres3, INPUT); 
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  pinMode(mosfetForSolenoide, OUTPUT);     

  Serial.begin(9600); 
}

 
void loop() {
  
  temp1 = digitalRead(llaveEscarabajoUno);           temp4 = digitalRead(llaveEscarabajoUno1);  
  temp2 = digitalRead(llaveEscarabajoDos);           temp5 = digitalRead(llaveEscarabajoDos2);  
  temp3 = digitalRead(llaveEscarabajoTres);         temp6 = digitalRead(llaveEscarabajoTres3);  
 
 
  if( (comparePairs(llaveEscarabajoUno,llaveEscarabajoUno1)) && (comparePairs(llaveEscarabajoDos,llaveEscarabajoDos2)) && (comparePairs(llaveEscarabajoTres,llaveEscarabajoTres3)))
  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  digitalWrite(mosfetForSolenoide,HIGH);
  }
  else{
  digitalWrite(correct, LOW);
  digitalWrite(incorrect, HIGH);
  digitalWrite(mosfetForSolenoide,LOW);
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
  
  

  
  
  
  

