//DO PROGRAM
#include <SPI.h>
#include <MFRC522.h>

//============ Parametros Configurables ============================

// Se define el uID del Tag, este se obtiene de la lectura del Tag 
// Se toman en pares y en minisculas y se escriben precedudos por 0x
// Ejemplo: Tag ID: 40EFF56A
// byte value[] = {0x40, 0xef, 0xf5, 0x6a};
byte value[] = {0x19, 0x52, 0x85, 0x9e};


// Puertos de salida hacia el Arduino Principal
// Modificar solo si es necesario
#define PRESENT_PIN     7
#define CORRECT_PIN     6

//=================================================================

#define RST_PIN         9          
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);   //Se crea el objeto MFRC522
MFRC522::MIFARE_Key key;

byte empty[] = {0x00,0x00,0x00,0x00};
byte buffer[4];
byte buffersize = sizeof(buffer);

void setup() {
    Serial.begin(9600); 
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    mfrc522.PCD_SetRegisterBitMask(mfrc522.RFCfgReg, (0x07<<4)); //Set Antena Gain to MAX

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
  
    pinMode(PRESENT_PIN,OUTPUT);
    pinMode(CORRECT_PIN,OUTPUT);
    digitalWrite(CORRECT_PIN,LOW);
    digitalWrite(PRESENT_PIN,LOW);
}

void loop() {
  
  ifCorrect();  
   
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()){
        digitalWrite(PRESENT_PIN,LOW);
        *buffer = *empty;
        return;
    }
    digitalWrite(PRESENT_PIN,HIGH);
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    //Realiza la lectura del uID del Tag
    for (int i = 0; i < 4; i++) {  //
    buffer[i] = mfrc522.uid.uidByte[i];
  }
}


bool compareByte(byte *buffer,  byte *value) {
    for (byte i = 0; i < buffersize; i++) 
        if(buffer[i]!=value[i]) 
            return false;
     return true;
}

void ifCorrect(){
  if(compareByte(buffer,value)){
    digitalWrite(CORRECT_PIN,HIGH);
    } 
  else {
    digitalWrite(CORRECT_PIN,LOW);
    }
}
