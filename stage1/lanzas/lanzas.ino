#include <Wire.h>
#include <pca9555.h>
#include <SoftwareSerial.h>
#include <MP3.h>


/*-------------- CONFIGURACIONES -------------------------------*/

const int soundStorage = 0; //almacenamiento de los sonidos , 0:USB , 1:SD
const int _n_levels=7;                //Número de elementos que contendrá la serie para ganar el juego
const unsigned char s[] = {0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,0x0009,0x0010};//Sonidos debe llevar el formato 0x + numero de indice a 4 digitos, (ej. para la primera es: 0x0001)
int serie_array[]={0,1,2,3};    //es la secuancia estatica que necesitamos ingresar {DO,RE,MI,FA,SOL,LA,SI}
const int solenoide = 3;
/*--------------------------------------------------------------*/

/** define mp3 class */
MP3 mp3;
pca9555 gpio(0x27);
pca9555 gpio2(0x20);
// Variables
int buttonState[] = {0,0,0,0,0,0,0};         // El estado actual de los botones
int lastButtonState[] = {0,0,0,0,0,0,0};     // El estado previo de los botones
int correctRFID[] = {0,0,0,0,0,0,0};
int blockedRFID[]={0,0,0,0,0,0,0}; // Se bloquean los RFID que hayan tenido una lectura incorrecta, hasta que el tag no esté presente
int currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int hole = 0;                 //el compartimiento secreto está cerrado
//Función que inicializa el vector de la serie y la variable currentValue
int currentlevel = 1; // es el nivel actual, es decir el numero de entradas correctas del usuari
int right = 0; //1 indica que el usuario ingresó un dato correcto , 0 indica que ha fallado
int n_levels = _n_levels; //niveles (se asigna el valor de _n_levels a n_levels por cuestiones de crear la memoria dinámicamente)
int binary[] = {1,2,4,8,16,32,64};
void setup() {
  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  /** set volum to the MAX */
  mp3.volume(0x1F);
  // put your setup code here, to run once:
  Serial.begin(38400);
  delay(100);
  gpio.begin();//
  gpio2.begin();//
  gpio.gpioPinMode(INPUT);
  gpio2.gpioPinMode(INPUT);
  pinMode(solenoide, INPUT);   

  reset();
}

void loop() {
  int buttonchange = 0;
  int buttonValue = 0;
  int j = 0; //la posición actual de la serie 
  reset(); // reset todas los estados
  while(hole == 1){
      if(!verifyPresentTags()){
          hole = 0;
      }
  }//Si el compartimiento secreto está abierto NO se hace nada hasta el reicio
  //Iniciamos el juego
  Serial.println("nicio del juego");
  while (!compareSerie()){
      printStatus2();
      digitalWrite(solenoide,LOW);
     //Mientras no haya cambio en los RFID, seguir con la lectura   
      while (buttonchange == 0){
        printStatus2();
        for (int i = 0; i < 7; i++){ 
                               
                buttonState[i] =readRFID(i);// digitalRead(i+2);
                
                buttonchange = buttonchange + buttonState[i];                  
            }
            delay(200);  
      }

      delay(300);
       buttonchange=0;      
  }
  openHole();
  
}

//--------FUNCTIONS--------//
//-----Begin Reset function -----//
// Reinicia los estados de los
void reset(){
  for(int i=0; i < 7;i++){
    lastButtonState[i] = 0;
    buttonState[i]=0;
    correctRFID[i] = 0;//{0,0,0,0,0,0,0};
    blockedRFID[i]=0;//{0,0,0,0,0,0,0};
  }
}
//--- End Reset
bool compareSerie(){
  for(int i=0; i<n_levels;i++){
    if(correctRFID[i]!=1){
      return false;
    }
  }
  return true;
}
bool readGpio(int index){
  if(index < 16){
    if(gpio.gpioDigitalRead(index))  return true;
    else return false;
  }
  else{
    if(gpio2.gpioDigitalRead(index-16)) return true;
    else return false;
  }
}

bool getPresentPin(int index){
  int i = index*4;
  return readGpio(i);
}

int getCodePin(int x){
  int i = x*4;
  int result =0;
  int index =0;
  bool value;
  for(int j=i+3;j>i;j--){
    value = readGpio(j);
    if(value){
      result+= binary[index];//(int)pow(2,index);
    }
    index++;
  } 
  return result;  
}

// Lee los pines de tag correcto y tag presente
int readRFID(int value){
  //printStatus2(); 
  int isPresent = getPresentPin(value);//gpio.gpioDigitalRead(value+8);
  int codePin = getCodePin(value);
  int isCorrect, sound;
  isCorrect = codePin == 7 ? 1:0;  
  //printStatus();
  if(!isPresent){
    blockedRFID[value] = 0;
    correctRFID[value] = 0;
  }else{
    printPresentCode(value,codePin);
  }
  if(blockedRFID[value]== 1){
    return 0;   
  }
  if(isCorrect && isPresent){
      playSound(s[value+1]);
      correctRFID[value] = 1;
      blockedRFID[value] = 1;
   }
  if(!isCorrect && isPresent){
      playSound(s[codePin+1]);
      blockedRFID[value] = 1;
      correctRFID[value] = 0;
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

void printPresentCode(int x,int calculate){
  int i = x*4;
  int result;
  int index =0;
  int value;
  Serial.println("");
  for(int j=i+3;j>i;j--){
    value = readGpio(j) ? 1:0;
    Serial.print(value);
    index++;
  } 
  Serial.print("  :  ");
  Serial.print(calculate);
  Serial.println("");
  
}
void printStatus2(){
  Serial.println("");
  for(int i=0; i< 8; i++){
    Serial.print(correctRFID[i]);
    Serial.print("");
  }
  Serial.println("");
}

void printStatus(){
  Serial.println("");
  for(int i=0; i< 8; i++){
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
  digitalWrite(solenoide,HIGH);//SOLENOIDE ON
  //servo.write(90);
}

bool verifyPresentTags(){
  for(int i=0; i<7;i++){
      if(getPresentPin(i)){
        return true;
      }
  }
  return false;
}
//--------END FUNCTIONS----//





