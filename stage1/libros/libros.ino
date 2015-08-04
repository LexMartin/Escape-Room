#include <Servo.h>

/*

Automatizacion - libros
Created by Cindy Canul Canul & Cristian Kumul Uc
E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
*/


// Variables, el numero descrito es el PIN a utilizar en la placa arduino.
// El numero no necesariamente tiene que ser el que esta descrito aqui, puede ser diferente.

int libroUno = 2; 
int libroDos = 3; 
int libroTres = 4; 

// Estas son por seguridad, en caso de que las primeras partes no funcionen

int libroUno1 = 5; // respaldo de parte uno del totem
int libroDos2  = 6; // respaldo parte dos
int libroTres3 = 7;  // respaldo parte tres

// validacion del juego
int correct = 13;  // Cuando las tres partes del totem estan correctas
int incorrect = 8; // el juego es incorrecto



// para servomotror
Servo servo; // se crea un objeto servo
int posicion; // posicion del servo
int servoActivo = 9;

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
  pinMode(libroUno, INPUT); 
  pinMode(libroDos, INPUT); 
  pinMode(libroTres, INPUT); 
  
  pinMode(libroUno1, INPUT); 
  pinMode(libroDos2, INPUT); 
  pinMode(libroTres3, INPUT); 
  
  // salidas
  pinMode(correct, OUTPUT);  
  pinMode(incorrect, OUTPUT); 
  pinMode(servoActivo, OUTPUT);     
  
  // servomotor
  servo.attach(10); // seleccionamos el PIN a usar.
  
  
  Serial.begin(9600); 
}

 
void loop() {
  
  temp1 = digitalRead(libroUno);           temp4 = digitalRead(libroUno1);  
  temp2 = digitalRead(libroDos);           temp5 = digitalRead(libroDos2);  
  temp3 = digitalRead(libroTres);         temp6 = digitalRead(libroTres3);  
 
 
  if( (comparePairs(libroUno,libroUno1)) && (comparePairs(libroDos,libroDos2)) && (comparePairs(libroTres,libroTres3)))
  {
  digitalWrite(correct, HIGH);
  digitalWrite(incorrect, LOW);
  temp = correct;
  temp = true;
  /*
  if(temp)
  {
    digitalWrite(z,HIGH);

  }
  */
  
  }
  else{
  digitalWrite(correct, LOW);
  digitalWrite(incorrect, HIGH);
  temp = correct;
  temp = false;
 
  
  
  }
  //Serial.println(comparePairs(ValTotem,OtherValTotem));
  
  
  
  // activacion del servo
    if(temp == HIGH)
  {
    digitalWrite(servoActivo,HIGH);
    posicion = 150;            // Establecemos el valor de la posicion a 150º  
    posicion = map(posicion, 0, 1023, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM  
    servo.write(posicion);                  // Escribimos la posicion con el mapa de valores al servo  
    delay(150);                           // Y le damos un tiempo para que sea capaz de moverse   

  }else{
   digitalWrite(servoActivo,LOW);
  
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
  
  

  
  
  
  

