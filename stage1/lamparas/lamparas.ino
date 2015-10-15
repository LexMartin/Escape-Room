
// Created by Cindy Canul Canul & Cristian Kumul Uc
// E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
#include <SoftwareSerial.h>
#include <MP3.h>
/** define mp3 class */
MP3 mp3;
const int _n_levels=5;                //Número de elementos que contendrá la serie para ganar el juego
// Variables
int inputPin[] = {2,3,4,5};           //Declaración de las entradas que se usarán
int ledPin[] = {9,10,11,12};            //Pines para los leds de la secuencia
int buttonState[] = {0,0,0,0};         // El estado actual de los botones
int lastButtonState[] = {0,0,0,0};     // El estado previo de los botones
int serie_array[_n_levels],currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int readyLed = 6;                      //Led que nos dará señal que espera la entrada del usuario
long previousMillis = 0;                //Variable para determinar el tiempo que ha pasado mientras el usuario no activa una entrada
long interval = 7000;                   //Intervalo de tiempo que se le permitirá al usuario entre cada entrada en ms
const unsigned char s[] = {0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0010};//Sonidos
const int soundStorage = 1; //almacenamiento de los sonidos , 0:USB , 1:SD





void setup() {
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  /** set volum to the MAX */
  mp3.volume(0x1F);
  randomSeed(analogRead(0)); //semilla para el pseudorandom
  //inicializamos las entradas y salidas
  for(int x = 0; x < 4; x=x+1)
  {
    pinMode(inputPin[x],INPUT);
    pinMode(ledPin[x],OUTPUT);
  }
  pinMode(readyLed,OUTPUT);
  // iniciamos la comunicación serial para imprimir por la salida estandar
  Serial.begin(9600); 
}
int game_on = 0;
int currentlevel = 1; // es el nivel actual, es decir el numero de entradas correctas del usuario
long rand_num = 0; //variable donde se almacena un numero pseudorandom
int rando = 0; 
int ledtime = 500; //tiempo que el led estará encendido cuando el usuario seleccione un botón
int pinLedSerie = 0; //Variable para almacenar el led que se encenderá al mostrar la secuencia
int right = 0; //1 indica que el usuario ingresó un dato correcto , 0 indica que ha fallado
int speedfactor = 5; 
int leddelay = 200; //delay de los leds
int n_levels =_n_levels; //niveles (se asigna el valor de _n_levels a n_levels por cuestiones de crear la memoria dinámicamente)


void loop() {
 
int i;
int n_pin = sizeof(inputPin)/sizeof(int); // Número de pines que serán nuestras entradas y salidas
//Iniciamos el juego
if (game_on == 0){
  getInitialArray(n_levels,n_pin);
  unsigned long currentMillisBegin = millis();
  previousMillis = currentMillisBegin;
  //Mostramos la secuencia del juego (cambiará tras el error)
  /*for (i = 0; i < n_levels; i= i + 1){
      leddelay = ledtime/(1+(speedfactor/n_levels)*(currentlevel - 1));
      pinLedSerie = serie_array[i];
      digitalWrite(pinLedSerie+7, HIGH);
      delay(leddelay);
      digitalWrite(pinLedSerie+7, LOW);
      delay(100/speedfactor);
 }*/
 game_on = 1; 

}




i = 0;
int buttonchange = 0;   
mp3.stop(); 
int j = 0; //la posición actual de la serie
while (j < n_levels){
  Serial.println("CurrentLEVEL");
  Serial.println(currentlevel);    
    while (buttonchange == 0 && game_on==1){
          digitalWrite(readyLed,HIGH);
          //waitPin(n_pin,ledPin[serie_array[currentlevel-1]]);
          digitalWrite(ledPin[serie_array[currentlevel-1]],HIGH);
          for (i = 0; i < 4; i = i + 1){ 
          buttonState[i] = readPIR(i+2);//digitalRead(i+2);
          buttonchange = buttonchange + buttonState[i];
        }
        unsigned long currentMillis = millis();

        if(currentMillis - previousMillis > interval)
        {
          //previousMillis = currentMillis;
          right = 0;
          break;
        }
        
        //Serial.println(ledPin[serie_array[currentlevel-1]]);
        delay(100);
    }
    digitalWrite(readyLed,LOW);
    digitalWrite(ledPin[serie_array[currentlevel-1]],LOW);
     for (i = 0; i < 4; i = i + 1){
        if (buttonState[i] == HIGH) {
            digitalWrite(ledPin[i], HIGH);
            delay(ledtime);
            digitalWrite(ledPin[i], LOW);
            
            currentValue=i; 
            buttonState[i] = LOW;
            buttonchange = 0;
            break;
         }
       } 
        if (currentValue == serie_array[j]){
            j++;  
            right = 1;
            }
        else{
          
            right = 0;
            i = 4;
            
        }

        // si la entrada es incorrecta se muestra una señal de error prendiendo todos los leds
        if (right == 0){
          delay(300);
          i = 0;
          game_on = 0;
          currentlevel = 1;
          //previousMillis = 0;
          Serial.println("Error!!!");
          for (i = 0; i < 4; i = i + 1){
                 digitalWrite(ledPin[i], HIGH);
              }
               delay(ledtime);   
           for (i = 0; i < 4; i = i + 1){
                 digitalWrite(ledPin[i], LOW);   
               }
               delay (200);
          for (i = 0; i < 4; i = i + 1){
                 digitalWrite(ledPin[i], HIGH);
              }
               delay(ledtime);  
           for (i = 0; i < 4; i = i + 1){
                 digitalWrite(ledPin[i], LOW);   
               }
               
               delay(500);
               game_on = 0;
               unsigned long currentMillisError = millis();
               previousMillis = currentMillisError;
               //salimos del while para iniciar un nuevo juego
               break;
               
        }


    //Si se inserta el valor correcto avanzamos al siguiente elemento de la serie
        if (right == 1){
            currentlevel++;
            Serial.println("Coorecto aumenta 1");
            Serial.println(currentlevel);
            unsigned long currentMillisOK = millis();
            previousMillis =currentMillisOK;
            
            }
         if(currentlevel == 2 ){
           playSound(s[random(0,2)]);
         }
        //si se llega al final de la secuencia el juego se ha ganado   
        if (currentlevel > n_levels){
          Serial.println("Ha ganado el juego");
          delay(500);
          // Se crea una serie automática cuando se ha ganado el juego
          int winSerie[] = {0, 1, 2, 3, 3, 2, 1, 0, 0};
          int tmp = 0;
          
          int delays[] = {50, 80, 100, 120, 160, 200, 240, 250, 300}; 
          for (i = 0; i < 9; i = i + 1){
            tmp = winSerie[i];
            digitalWrite(ledPin[tmp], HIGH);
            delay(200);
            digitalWrite(ledPin[tmp], LOW);
            delay(delays[i]);
          }
          //El juego se ha terminado
          game_on = 0;
          currentlevel = 1;
          
         }    
}
 
}

//FUNCTIONS--------------------

void playSound(char sound){
  if(soundStorage==0){
    mp3.play_usb_disk(sound);
  }
  if(soundStorage==1){
    mp3.play_sd(sound);
  }
}


//Función que inicializa el vector de la serie y la variable currentValue
void getInitialArray(int n,int n_pin)
{
  Serial.println("N_PIN");
  Serial.println(n_pin);
  Serial.println("/N_PIN");
  int rand_num,random_selected;
  for(int i=0; i<n; i=i+1){
        serie_array[i]=0;
        currentValue = 0;
        rand_num = random(0,n_pin);
        if(i>0)
        {
          while(rand_num == serie_array[i-1]) //Nunca habrá dos digitos iguales consecutivos
          {
            rand_num = random(0,n_pin);
          }
        }
        Serial.println(rand_num);
        random_selected = rand_num;
        serie_array[i]=random_selected;    //guardamos el valor pseudorandom seleccionado
      }

    
}

//Función para leer el cambio en los sensores PIR
int readPIR(int pinPir)
{
  int readPin = digitalRead(pinPir);

  return readPin;
}

//Función para encender el led que esperamos en la secuencia

void waitPin(int n,int led)
{
  for(int i = 0; i<n;i=i+1)
  {
    if(ledPin[i] != ledPin[led])
    {
      digitalWrite(ledPin[i],LOW);
    }
    else
    {
      digitalWrite(ledPin[i],HIGH);
    }
  }
}
