#include <Wire.h>
#include <pca9555.h>
#include <SoftwareSerial.h>
#include <MP3.h>
#include <Servo.h>


/*-------------- CONFIGURACIONES -------------------------------*/

const int soundStorage = 0; //almacenamiento de los sonidos , 0:USB , 1:SD
const int _n_levels=8;                //Número de elementos que contendrá la serie para ganar el juego
const unsigned char s[] = {0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0010};//Sonidos debe llevar el formato 0x + numero de indice a 4 digitos, (ej. para la primera es: 0x0001)
/*
N = 0
S = 1
E = 2
W = 3

*/
int serie_array[]={0,1,2,3,2,1,0,2};    //es la secuancia estatica que necesitamos ingresar
/*--------------------------------------------------------------*/

/** define mp3 class */
MP3 mp3;
pca9555 gpio(0x27);
Servo servo;
// Variables
int buttonState[] = {0,0,0,0};         // El estado actual de los botones
int blockedRFID[]={0,0,0,0}; // Se bloquean los RFID que hayan tenido una lectura incorrecta, hasta que el tag no esté presente
int inputSerie[]= {9,9,9,9,9,9,9,9};
int currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int hole = 0;                 //el compartimiento secreto está cerrado
//Función que inicializa el vector de la serie y la variable currentValue
int currentlevel = 1; // es el nivel actual, es decir el numero de entradas correctas del usuari
int right = 0; //1 indica que el usuario ingresó un dato correcto , 0 indica que ha fallado
int n_levels = _n_levels; //niveles (se asigna el valor de _n_levels a n_levels por cuestiones de crear la memoria dinámicamente)



void setup() {
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  /** set volum to the MAX */
  mp3.volume(0x1F);
  // put your setup code here, to run once:
  Serial.begin(38400);
  delay(100);
  gpio.begin();//
  gpio.gpioPinMode(INPUT);
  servo.attach(3);
  servo.write(0);
  reset();
}

void loop() {
  int buttonchange = 0;
  int buttonValue = 0;
  int j = 0; //la posición actual de la serie 
  reset(); // reset todas los estados
  while(hole == 1){  }//Si el compartimiento secreto está abierto NO se hace nada hasta el reicio
  //Iniciamos el juego
   while (!compareSerie()){
      Serial.println("CurrentLEVEL");
      Serial.println(currentlevel); 
      //Mientras no haya cambio en los RFID, seguir con la lectura   
      while (buttonchange == 0){
        for (int i = 0 ; i < 4; i = i+1){                 
                buttonState[i] =readRFID(i);// digitalRead(i+2);
                buttonchange = buttonchange + buttonState[i];                  
            }
            delay(200);
       }
      //Evaluamos el cambio, de acuerdo a los estados
      for (int i = 0; i < 4; i = i + 1){
          if (buttonState[i] == HIGH) {       
                delay(200);
                buttonValue = buttonState[i];
                currentValue=i; 
                buttonState[i] = LOW;
                buttonchange = 0;
                break;
                
             }
        }
        push(currentValue);
        printList();
         
  }
  
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
  //printStatus();
  if(!isPresent){
    blockedRFID[value] = 0;
  }
  if(blockedRFID[value]== 1){
    return 0;   
  }
  if(isCorrect && isPresent){
      playSound(s[value]);
   }
  if(!isCorrect && isPresent){
      Serial.print("Error tag incorrecto");
      Serial.print(isCorrect);
      Serial.print(" - ");
      Serial.print(isPresent);
      Serial.println("");
      playSound(s[8]);
      blockedRFID[value] = 1;
      //return 2;
      
   }
  if(isCorrect  && isPresent){
    //playSound(s[value]);
    return 1;
  }
  else{
    return 0;
  }
}

void printStatus(){
  Serial.println("");
  for(int i=0; i< 4; i++){
    Serial.print(blockedRFID[i]);
    Serial.print("");
  }
  Serial.println("");
}
void playSound(char sound){
  if(soundStorage==0){
    mp3.play_usb_disk(sound);
  }
  if(soundStorage==1){
    mp3.play_sd(sound);
  }
}

void openHole()
{
  hole = 1; // se abre el compartimiento secreto
  Serial.println("Se abre el compartimiento, juego ganado");
  servo.write(90);
}

bool verifyPresentTags(){
  for(int i=0; i<n_levels;i++){
      if(gpio.gpioDigitalRead(i+8)){
        return true;
      }
  }
  return false;
}
//--------END FUNCTIONS----//

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

bool compareSerie(){
  for(int i=0; i<n_levels;i++){
    if(inputSerie[i]!=serie_array[i]){
      return false;
    }
  }
  return true;
}




