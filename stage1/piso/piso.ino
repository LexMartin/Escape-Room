const int _n_levels=5;                //Número de elementos que contendrá la serie para ganar el juego
// Variables
int inputPin[] = {2,3,4,5};           //Declaración de las entradas que se usarán
int ledPin[] = {7,8,9,10};            //Pines para los leds de la secuencia
int buttonState[] = {0,0,0,0};         // El estado actual de los botones
int lastButtonState[] = {0,0,0,0};     // El estado previo de los botones
int serie_array[_n_levels],currentValue; //vectores donde se almacenará la serie y currentValue es donde almacenaremos el valor de la selección del usuario en tiempo de ejecución
int readyLed = 12;                      //Led que nos dará señal que espera la entrada del usuario
int secretChamber = 0;                 //el compartimiento secreto está cerrado
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
        //Serial.println(rand_num); //N=0 ,S=1,W=2,E=3
        switch(rand_num)
        {
          case 0:
            Serial.println("N");
            break;
          case 1:
            Serial.println("S");
            break;
          case 2:
            Serial.println("W");
            break;
          case 3:
            Serial.println("E");
            break;
        }
        random_selected = rand_num;
        serie_array[i]=random_selected;    //guardamos el valor pseudorandom seleccionado
      }

    
}

int readRFID(int value){
  int readValue = digitalRead(value);
  return readValue;

}

void openSecretChamber()
{
  secretChamber = 1; // se abre el compartimiento secreto
  Serial.println("Se abre el compartimiento secreto");
}

void setup() {
  
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
while(secretChamber == 1){} //Si el compartimiento secreto está abierto NO se hace nada hasta el reicio
int n_pin = sizeof(inputPin)/sizeof(int); // Número de pines que serán nuestras entradas y salidas
//Iniciamos el juego
if (game_on == 0){
  getInitialArray(n_levels,n_pin);
  
 
 game_on = 1; 

}




i = 0;
int buttonchange = 0;    
int j = 0; //la posición actual de la serie
while (j < n_levels){
  Serial.println("CurrentLEVEL");
  Serial.println(currentlevel);    
    while (buttonchange == 0){
          for (i = 0; i < 4; i = i + 1){ 
          buttonState[i] =readRFID(i+2);// digitalRead(i+2);
          buttonchange = buttonchange + buttonState[i];
        }
        digitalWrite(readyLed,HIGH);
        delay(100);
    }
    digitalWrite(readyLed,LOW);
     for (i = 0; i < 4; i = i + 1){
        if (buttonState[i] == HIGH) {
            digitalWrite(i+7, HIGH);
            delay(ledtime);
            digitalWrite(i+7, LOW);
            
            currentValue=i; 
            buttonState[i] = LOW;
            buttonchange = 0;
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
          Serial.println("Error!!!");
          for (i = 0; i < 4; i = i + 1){
                 digitalWrite(i+7, HIGH);
              }
               delay(ledtime);   
           for (i = 0; i < 4; i = i + 1){
                 digitalWrite(i+7, LOW);   
               }
               delay (200);
          for (i = 0; i < 4; i = i + 1){
                 digitalWrite(i+7, HIGH);
              }
               delay(ledtime);  
           for (i = 0; i < 4; i = i + 1){
                 digitalWrite(i+7, LOW);   
               }
               
               delay(500);
               game_on = 0;
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
          delay(500);
          openSecretChamber(); //Se abre el compartimiento secreto
          
          //El juego se ha terminado
          game_on = 0;
          currentlevel = 1;
          
         }

        
}





 
}