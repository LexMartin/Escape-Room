//DO PROGRAM
#include <SPI.h>
#include <MFRC522.h>

//============ Parametros Configurables ============================

// Se define el uID del Tag, este se obtiene de la lectura del Tag 
// Se toman en pares y en minisculas y se escriben precedudos por 0x
// Ejemplo: Tag ID: 40EFF56A
// byte value[] = {0x40, 0xef, 0xf5, 0x6a};
byte value[] = {0x19, 0x52, 0x85, 0x9e};

//=================================================================

#define RST_PIN         9          
#define SS_PIN          10          
#define PRESENT_PIN     8
#define CORRECT_PIN     7

MFRC522 mfrc522(SS_PIN, RST_PIN);   //Se crea el objeto MFRC522
MFRC522::MIFARE_Key key;

byte last[] = {0x00,0x00,0x00,0x00};
byte status;
byte buffer[4];
byte size = sizeof(buffer);



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
  
    pinMode(PRESENT_PIN,OUTPUT);
    pinMode(CORRECT_PIN,OUTPUT);
    digitalWrite(CORRECT_PIN,LOW);
    digitalWrite(PRESENT_PIN,LOW);
}

void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()){
        digitalWrite(PRESENT_PIN,LOW);
        return;
    }
    digitalWrite(PRESENT_PIN,HIGH);
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    //Realiza la lectura del uID del Tag
    for (int i = 0; i < 4; i++) {  //
    buffer[i] = mfrc522.uid.uidByte[i];
    //Serial.print(readCard[i], HEX);   //Debug
  }
    //Serial.println();                   //Debug
   
     
    if(compareByte(buffer,sizeof(value),value))
    {
      digitalWrite(CORRECT_PIN,HIGH);
      Serial.println("TRUE");
    }
    else
    {
      digitalWrite(CORRECT_PIN,LOW);
      Serial.println("FALSE");
    }
}


bool compareByte(byte *buffer, byte bufferSize , byte *value) {
    int cont = 0;
    for (byte i = 0; i < bufferSize; i++) {
        last[i] = value[i];
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
