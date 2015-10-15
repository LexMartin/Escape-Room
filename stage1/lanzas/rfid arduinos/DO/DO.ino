//DO PROGRAM
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable
#define SS_PIN          10          // Configurable
#define PRESENT_PIN     8
#define CORRECT_PIN     7
MFRC522 mfrc522(SS_PIN, RST_PIN);   //Se crea el objeto MFRC522

MFRC522::MIFARE_Key key;

byte sector         = 0;
byte blockAddr      = 1;

/*
 * DO : {0x44, 0x4f}
 * RE : {0x52, 0x45}
 * MI : {0x4d, 0x49}
 * FA : {0x46, 0x41}
 */
byte value[] = {0x52 ,0x45}; // nota musical
byte last[] = {0x00,0x00};
byte status;
byte buffer[18];
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
      digitalWrite(CORRECT_PIN,HIGH);
      Serial.println("TRUE");
    }
    else
    {
      digitalWrite(CORRECT_PIN,LOW);
      Serial.println("FALSE");
    }
    
    
   
    
    // Halt PICC
   
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
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
