//TIEMPOS CORRECCION
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

/*--------------Configuraciones ------------------------*/
#define  servoPin 3 // Pin del Output del Servo   
#define Cerradura  4 //Pin de salida para la CERRADURA

byte value[] = {0x44, 0x49, 0x43, 0x45}; // D,I,C,E  

int timeWinner = 2 * 1000;  // Segundos antes de reiniciar el juego
const int servoDelay = 1 * 1000; // tiempo apertura cierre del Servo

const int OPEN = 180; //Angulo de apertura del Servo
const int CLOSE = 0; // Angulo de Cierre del Servo
/*------------------------------------------------------*/


// ----------  Parametros Internos NO MODIFICAR 

const int LOCK=LOW;
const int UNLOCK=HIGH;

#define RST_PIN         9           // Configurable opcional
#define SS_PIN          10          // Configurable opcional

MFRC522 mfrc522(SS_PIN, RST_PIN);   //Se crea el objeto MFRC522
Servo servo;
MFRC522::MIFARE_Key key;

byte sector         = 0;
byte blockAddr      = 1;

byte status;
byte buffer[18];
byte size = sizeof(buffer);
//--------------------------------

void setup() {
    Serial.begin(9600); 
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
    int servoPos = 0;
    servo.attach(servoPin);
    pinMode(Cerradura,OUTPUT);
    digitalWrite(Cerradura,LOCK);
    
}

/**
 * Main loop.
 */
void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    

    // Authenticate using key A
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    // Read data from the block
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    //dump_byte_array(buffer, 16);
    if(compareByte(buffer,sizeof(value),value))
    {
      winner();
    }
    else
    {
      throwBack();
    }
    
        

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}

void throwBack()
{
  Serial.println("Tirar de nuevo");
  digitalWrite(Cerradura,LOCK);
 
  servo.write(OPEN);
  delay(servoDelay);
  servo.write(CLOSE);
  
}

void winner()
{
  Serial.println("GANADOR");
  digitalWrite(Cerradura,UNLOCK);
  delay(timeWinner);
  throwBack();
  
  
}
bool compareByte(byte *buffer, byte bufferSize , byte *value) {
    int cont = 0;
    for (byte i = 0; i < bufferSize; i++) {
        
        if(buffer[i]!=value[i])
        {
          cont = 1;
        }
    }

    if(cont == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
}
