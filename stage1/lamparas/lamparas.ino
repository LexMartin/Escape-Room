
// Created by Cindy Canul Canul & Cristian Kumul Uc
// E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com
#include "HX711.h"
#include <SoftwareSerial.h>
#include <MP3.h>


/** define mp3 class */

//
//  Sensor de Peso 50Kg --------- HX711
//  Blanco ----------------------- E+
//  Negro  ----------------------- E- 
//  Blanco ---Resistencia---+
//                          +----- A-
//  Negro  ---Resistencia --+
//  Rojo   ----------------------- A+

//-------------CONFIGURACIONES---------------------------------------------------------------------------------------------------------------//
const int _n_levels=10;                //Número de elementos que contendrá la serie para ganar el juego
int ledPin[] = {22,24,26,28,30,32,34};            //Pines para los leds de la secuencia// Serán los relays para las lamparas
long interval = 3 * 1000;                   //Intervalo de tiempo que se le permitirá al usuario entre cada entrada en ms
const unsigned char s[] = {0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0010};//Sonidos
const int soundStorage = 0; //almacenamiento de los sonidos , 0:USB , 1:SD
int secretCompartment = 35;
//------------/CONFIGURACIONES---------------------------------------------------------------------------------------------------------------//





//Sensores de peso
HX711 Peso1(A1, A0);  
HX711 Peso2(A3, A2);
HX711 Peso3(A5, A4);
HX711 Peso4(A9, A8);
HX711 Peso5(A11, A10);
HX711 Peso6(A13, A12);
HX711 Peso7(A15, A14);
HX711 sensors[] = {Peso1,Peso2,Peso3,Peso4,Peso5,Peso6,Peso7};
const float Umbral=300.0;

MP3 mp3;

int buttonState[] = {0,0,0,0,0,0,0};         // El estado actual de los botones
int lastButtonState[] = {0,0,0,0,0,0,0};     // El estado previo de los botones
int serie_array[_n_levels],currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int readyLed = 6;                      //Led que nos dará señal que espera la entrada del usuario
long previousMillis = 0;                //Variable para determinar el tiempo que ha pasado mientras el usuario no activa una entrada
float umbrals[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int correctUmbral[] = {0,0,0,0,0,0,0};
int startButton = 17; //Entrada para iniciar y reiniciar el juego (taza) ya sea con sensor hall o con sensor IR
int game_on = 1;
int currentlevel = 0; // es el nivel actual, es decir el numero de entradas correctas del usuario
int n_levels =_n_levels; //niveles (se asigna el valor de _n_levels a n_levels por cuestiones de crear la memoria dinámicamente)



void setup() {
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  /** set volum to the MAX */
  mp3.volume(0x1F);
  randomSeed(analogRead(0)); //semilla para el pseudorandom
  //inicializamos las entradas y salidas
  for(int x = 0; x < 7; x=x+1)
  {
    
    pinMode(ledPin[x],OUTPUT);
  }

  for(int x = 0; x < 7; x++)
  { 
    digitalWrite(ledPin[x],HIGH);
    //delay(400);
    //digitalWrite(ledPin[x],LOW);
    
  }
  delay(400);
  for(int x = 0; x < 7; x++)
  { 
    //digitalWrite(ledPin[x],HIGH);
    //delay(400);
    digitalWrite(ledPin[x],LOW);
    
  }
  pinMode(secretCompartment,OUTPUT);
  pinMode(startButton,INPUT);
  //Iniciar la escala de los sensores
  

 
  // iniciamos la comunicación serial para imprimir por la salida estandar
  Serial.begin(9600); 

     float cal2 = 0;
   for (int i = 0; i < 7; i++){
      sensors[i].set_scale(2280.f);
      sensors[i].tare();
    
   }
   getUmbrals();

   game_on = 0;
   
}


void loop() {
 
int i;
int n_pin = 7 // Número de pines que serán nuestras entradas y salidas

game_on = digitalRead(startButton);
//Iniciamos el juego
if (game_on == 1){
  digitalWrite(secretCompartment,LOW);
  getInitialArray(n_levels,n_pin);
  unsigned long currentMillisBegin = millis();
  previousMillis = currentMillisBegin;

  game_on = digitalRead(startButton);

}




i = 0;
int buttonchange = 0;   
mp3.stop(); 
int j = 0; //la posición actual de la serie
currentlevel = 0;
while (currentlevel < n_levels){
  Serial.println("CurrentLEVEL");
  Serial.println(currentlevel);
  bool currentSensorValue =readPIR(serie_array[j]);
  bool correct = true;
  while(HIGH){      
      
      Serial.println("---------------------------------");
      unsigned long currentMillis = millis();      
      if(currentMillis - previousMillis > interval)
      {
        previousMillis = currentMillis;
        correct = false;
        break;
      }   
      digitalWrite(ledPin[serie_array[j]],HIGH);
      currentSensorValue =readPIR(serie_array[j]);
      if(currentSensorValue){
        correct = true;
        break;
      }
      delay(6);
    }
    
    digitalWrite(readyLed,LOW);
    digitalWrite(ledPin[serie_array[j]],LOW);
     
    if (correct){
        j++;  
        currentlevel++;
        Serial.println("Coorecto aumenta 1");
        Serial.println(currentlevel);
        unsigned long currentMillisOK = millis();
        previousMillis =currentMillisOK;
        game_on = 0;
        
    }else{
        Serial.println("Error: ");
        Serial.print(currentValue);
        Serial.println("");
        game_on = 0;
        currentlevel = 0;
        getInitialArray(n_levels,n_pin);
        previousMillis = millis();
        mp3.stop(); 
        j = 0;
        delay(30);
    }

    if(j == 1 ){
           playSound(s[0]);
     }

        // si la entrada es incorrecta se muestra una señal de error prendiendo todos los leds
       

    
       /*
        //si se llega al final de la secuencia el juego se ha ganado   
        if (currentlevel > 4){
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
         */    
    }
    winner();
    game_on =0;
 
}//main loop

//FUNCTIONS--------------------
void winner(){
  Serial.println("Ha ganado el juego");
  digitalWrite(secretCompartment,LOW);
  delay(2000);
}
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

  int rand_num,random_selected;
  for(int i=0; i<n; i++){
        serie_array[i]=0;
        currentValue = 0;
        rand_num = random(0,n_pin);
        if(i>0)
        {
          while(rand_num == serie_array[i-1]) //NO dos digitos  consecutivos
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
bool readPIR(int index)
{ 
  
  float tmp = pow(sensors[index].get_units(3),2);
  float dif = tmp - umbrals[index];
  if(dif > 35000.0 && correctUmbral[index] == 0){
    umbrals[index] = tmp;
    correctUmbral[index] = 1;
  }
  Serial.println("");
  Serial.print(tmp);
  Serial.print("|");

  float compare = sqrt(pow(tmp -umbrals[index],2));
  
  float estimate = umbrals[index]+(umbrals[index]* 0.05); 
  Serial.print(umbrals[index]);
  Serial.print("|");
  Serial.print(compare );
  Serial.println("");
  int result = 0;
  
  result = compare > 20000.0 ? HIGH:LOW;
  
  sensors[index].power_down();              // put the ADC in sleep mode
  //delay(5000);
  sensors[index].power_up();
  return result;  
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

void getUmbrals(){
   float cal2 = 0;
   for (int i = 0; i < 7; i++){
  
        cal2=sensors[i].get_units(3);
         umbrals[i] = pow(cal2,2);
          delay(100);     
   }
}

