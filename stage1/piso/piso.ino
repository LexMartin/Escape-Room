// Created by Cindy Canul Canul & Cristian Kumul Uc
// E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com

#include <Wire.h>
#include <pca9555.h>
#include <SoftwareSerial.h>
#include <MP3.h>
#include <Servo.h>


/*-------------- CONFIGURACIONES -------------------------------*/

const int soundStorage = 0; //almacenamiento de los sonidos , 0:USB , 1:SD
const int _n_levels=8; //Número de elementos que contendrá la serie para ganar el juego
const unsigned char s[] = {0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0010};//Sonidos debe llevar el formato 0x + numero de indice a 4 digitos, (ej. para la primera es: 0x0001)
/*
N = 0
S = 1
E = 2
W = 3

*/
int serie_array[]={0,1,2,3,2,1,0,2};    //es la secuancia estatica que necesitamos ingresar (debe coincidir con el número _n_levels, de otro modo el programa no funcionara)

int inputSerie[]= {9,9,9,9,9,9,9,9};  
//es la serie que será comparada, al inicio esta lleno de 9 como valor incial, 
//mientras el usuario ingresa la secuencia se reemplaza el primer elemento y se recorren los demás índices

const int OPEN = 180; //Angulo de apertura del Servo
const int CLOSE = 0; // Angulo de Cierre del Servo
const int servoDelay = 1 * 1000; // tiempo apertura cierre del Servo
const int restartDelay = 3 * 1000; //tiempo de reinicio del juego

/*---------------FIN CONFIGURACIONES ---------------------------*/


MP3 mp3;
pca9555 gpio(0x27);
//Servo servo;
// Variables no configurables
int buttonState[] = {0,0,0,0};         // El estado actual de los botones
int currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int hole = 0;                 //el compartimiento secreto está cerrado
//Función que inicializa el vector de la serie y la variable currentValue
int n_levels = _n_levels; //niveles (se asigna el valor de _n_levels a n_levels por cuestiones de crear la memoria dinámicamente)


void setup() {
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  /** set volum to the MAX */
  mp3.volume(0x1F);
  Serial.begin(38400);
  delay(100);
  gpio.begin();//
  gpio.gpioPinMode(INPUT);
  pinMode(3, OUTPUT);   //PIN PARA MOSFET
  reset();
}

void loop() {
  int buttonchange = 0;
  reset(); // reset todos los estados almacenados
  while(hole == 1){ 
      delay(restartDelay);
      software_Reset();
  }//Si el compartimiento secreto está abierto NO se hace nada hasta el reicio
  //Iniciamos el juego
  Serial.println("Inicio del juego");
  //Se itera el algoritmo hasta que la serie sea igual a lo esperado, (hasta que serie_array sea igual a inputSerie)
   while (!compareSerie()){
      //Mientras no haya cambio en los RFID, seguir con la lectura   
      while (buttonchange == 0){
        for (int i = 0 ; i < 4; i = i+1){                 
                buttonState[i] =readRFID(i);// se almacena el valor devuelto de la lectura del RFID iésimo
                buttonchange = buttonchange + buttonState[i];  
                delay(60);                
            }
            delay(200);
       }
      //Evaluamos el cambio, de acuerdo a los estados
      for (int i = 0; i < 4; i = i + 1){
         //Encontramos el índice que fue seleccionado
          if (buttonState[i] == HIGH) {       
                delay(200);
                currentValue=i; //El índice seleccionado se almacena en 'currentValue'
                buttonState[i] = LOW;//se pone en false la bandera 
                buttonchange = 0;//reiniciamos nuestra variable del cambio
                break; //se rompe el ciclo
                
             }
        }
        //Agregamos a la cola, el valor seleccionado
        push(currentValue);
        //Se imprime la cola 
        printList();
        delay(2000);//Delay de la lectura
  }//fin del ciclo principal
  
  //Se ingresó la serie correctam
  openHole();
  
}

//--------FUNCTIONS--------//

//-----Begin Reset function -----//
// Reinicia los estados de los
void reset(){
  for(int i=0; i < 4;i++){
    buttonState[i]=0;
  }
}
//--- End Reset

// Lee los pines de tag correcto y tag presente
int readRFID(int value){
  int isCorrect =gpio.gpioDigitalRead(value);
  int isPresent = gpio.gpioDigitalRead(value+8);
  int sound;
  if(!isCorrect && isPresent){
     
      playSound(s[1]);
      push(9);
      printList();
      //return 2;     
   }
  if(isCorrect  && isPresent){
    playSound(s[1]);
    return 1;
  }
  else{
    return 0;
  }
}


void playSound(char sound){
  if(soundStorage==0){
    mp3.play_usb_disk(sound);
  }
  if(soundStorage==1){
    mp3.play_sd(sound);
  }
}

//funcion ganadora
void openHole()
{
  hole = 1; // se abre el compartimiento secreto
  Serial.println("Se abre el compartimiento, juego ganado");
  digitalWrite(3,HIGH);
  delay(servoDelay);
  digitalWrite(3,HIGH);
}


//funcion que agrega el elemento seleccionado al final de nuestro array y recorre los existentes
void push(int element){
  int tmp;
  for(int i=0; i<n_levels;i++){
    inputSerie[i] = inputSerie[i+1];
  }
  inputSerie[n_levels-1] = element; 
}

void printList(){
  Serial.println("");
  Serial.print("List :");
  for(int i=0; i<n_levels;i++){
    Serial.print(inputSerie[i]);
  }
  Serial.print("");
}
//Funcion que compara los datos ingresados por el usuario con la serie esperada
bool compareSerie(){
  for(int i=0; i<n_levels;i++){
    if(inputSerie[i]!=serie_array[i]){
      return false;
    }
  }
  return true;
}
void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");  
} 
//--------END FUNCTIONS----//

