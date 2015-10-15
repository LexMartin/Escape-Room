#include <Wire.h>
#include <pca9555.h>
#include <SoftwareSerial.h>
#include <MP3.h>
#include <Servo.h>

/** define mp3 class */
MP3 mp3;
pca9555 gpio(0x25);
Servo servo;

const int soundStorage = 0; //almacenamiento de los sonidos , 0:USB , 1:SD
const int _n_levels=4;                //Número de elementos que contendrá la serie para ganar el juego
const unsigned char s[] = {0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0010};//Sonidos
// Variables
int inputPin[] = {2,3,4,5};           //Declaración de las entradas que se usarán  .. FALTA MODIFICAR A 7 ENTRADAS QU SERAN LOS RFID
int buttonState[] = {0,0,0,0};         // El estado actual de los botones
int lastButtonState[] = {0,0,0,0};     // El estado previo de los botones
int serie_array[]={0,1,2,3};    //es la secuancia estatica que necesitamos ingresar {DO,RE,MI,FA,SOL,LA,SI}
int currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int readyLed = 12;                      //Led que nos dará señal que espera la entrada del usuario
int hole = 0;                 //el compartimiento secreto está cerrado
//Función que inicializa el vector de la serie y la variable currentValue
int game_on = 0;
int currentlevel = 1; // es el nivel actual, es decir el numero de entradas correctas del usuari
int right = 0; //1 indica que el usuario ingresó un dato correcto , 0 indica que ha fallado
int speedfactor = 5; 
int leddelay = 200; //delay de los leds
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
  

}

void loop() {
  int i=0;
  int buttonchange = 0;
  int buttonValue = 0;
  int j = 0; //la posición actual de la serie  
  int n_pin = sizeof(inputPin)/sizeof(int); // Número de pines que serán nuestras entradas y salidas
  while(hole == 1){}//Si el compartimiento secreto está abierto NO se hace nada hasta el reicio
  //Iniciamos el juego
  if (game_on == 0){
     
     game_on = 1; 
   }

   while (j < n_levels){
    Serial.println("CurrentLEVEL");
    Serial.println(currentlevel);    
      while (buttonchange == 0){
            for (i = 0; i < 4; i = i+1){             
                buttonState[i] =readRFID(i);// digitalRead(i+2);
                buttonchange = buttonchange + buttonState[i]; 
          }
          //Serial.println("Huboo un cambio");
          //digitalWrite(readyLed,HIGH);
          delay(200);
      }
     Serial.println("Huboo un cambio");
       for (i = 0; i < 4; i = i + 1){
          if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
             
              delay(200);
              buttonValue = buttonState[i];
              currentValue=i; 
              buttonState[i] = LOW;
              lastButtonState[i] = HIGH;
              buttonchange = 0;
              
           }
         } 
          if (currentValue == serie_array[j]){
              j++;  
              right = 1;
              }
          else {          
              right = 0;
                         
            }
  
          // si la entrada es incorrecta se muestra una señal de error prendiendo todos los leds
          if (right == 0){
            delay(300);
            i = 0;
            game_on = 0;
            currentlevel = 1;
            playSound(s[7]);
            Serial.println("Error!!!");         
            delay(500);
            game_on = 0;
            reset();
            //salimos del while para iniciar un nuevo juego
            break;
                 
          }
  
  
      //Si se inserta el valor correcto avanzamos al siguiente elemento de la serie
          if (right == 1){
              currentlevel++;
              Serial.println("Coorecto aumenta 1");
              Serial.println(currentlevel);
              
              }
          //si se llega al final de la secuencia el juego se ha ganado   
          if (currentlevel > n_levels){
            Serial.println("Ha ganado el juego");
            playSound(s[9]);
            delay(500);
            openHole(); //Se abre el compartimiento secreto
            
            //El juego se ha terminado
            game_on = 0;
            currentlevel = 1;
            
           }

        
  }


}

//--------FUNCTIONS--------//

void reset(){

  for(int i=0; i < 4;i++){
    lastButtonState[i] = 0;
    buttonState[i]=0;
  }
}
int readRFID(int value){

  int isCorrect =gpio.gpioDigitalRead(value);
  int isPresent = gpio.gpioDigitalRead(value+8);
  int sound;


  if(isCorrect && isPresent){
      Serial.println("Nota musical: ");
      Serial.print(isCorrect);
      Serial.print(isPresent);
      Serial.println("");
      playSound(s[value]);
   }
  if(!isCorrect && isPresent){
      Serial.print("Error tag incorrecto");
      Serial.print(isCorrect);
      Serial.print(isPresent);
      Serial.println("");
      playSound(s[8]);
      //return 2;
      
   }
  

  if(isCorrect  && isPresent  && lastButtonState[value] == 0){
    //playSound(s[value]);
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

void openHole()
{
  hole = 1; // se abre el compartimiento secreto
  Serial.println("Se abre el compartimiento, juego ganado");
  servo.write(90);
}

//--------END FUNCTIONS----//





