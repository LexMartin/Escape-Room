#include <SPI.h>
#include <MFRC522.h>







//DO PROGRAM


//============ Parametros Configurables ============================

// Se define el uID del Tag, este se obtiene de la lectura del Tag 
// Se toman en pares y en minisculas y se escriben precedudos por 0x
// Ejemplo: Tag ID: 40EFF56A 29 76 7F 9E
// byte value[] = {0x29, 0x76, 0x7f, 0x9e};
// DO : 0x29, 0x76, 0x7f, 0x9e
// RE : C9 2A 82 9E
// MI : 49 35 7B 9E / 0x19, 0x52, 0x85, 0x9e
// FA : C9 5C 7C 9E

//Value es el UID del TAG que se quiere grabar en el arduino osea una nota musical
byte value[] = {0x05, 0x6f, 0xfa, 0xe5};

//Aqui se colocan todos lo UID de las notas musicales, siguiendo el formato
byte allTags[][7] = {
                     {0x89, 0x34, 0x7c, 0x9e}, //DO
                     {0x39, 0xbb, 0x80, 0x9e}, //RE
                     {0x69, 0xc7, 0x7f, 0x9e}, //MI
                     {0x29, 0x6f, 0x7e, 0x9e}, //FA
                     {0xe9, 0xab, 0x50, 0xe5}, //SOL
                     {0x19, 0xa1, 0x78, 0x9e}, //LA
                     {0x05, 0x6f, 0xfa, 0xe5}, //SI
                   };


// Puertos de salida hacia el Arduino Principal
// Modificar solo si es necesario
#define PRESENT_PIN     7

#define FIRST_BIT       6
#define SECOND_BIT      5
#define THIRD_BIT       4

/*FBit  SBit  TBit  RESULT
 * 0    0    0     DO
 * 0    0    1     RE
 * 0    1    0     MI
 * 0    1    1     FA
 * 1    0    0     SOL
 * 1    0    1     LA
 * 1    1    0     SI
 * 1    1    1     CORRECT PIN
 * 
 */

//=================================================================

#define RST_PIN         9          
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);   //Se crea el objeto MFRC522
MFRC522::MIFARE_Key key;
int  statusval[] = {0,0,0,0}; 
byte empty[] = {0x00,0x00,0x00,0x00};
byte buffer[4];
byte buffersize = sizeof(buffer);

const int one = 1;

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
    pinMode(FIRST_BIT,OUTPUT);
    pinMode(SECOND_BIT,OUTPUT);
    pinMode(THIRD_BIT,OUTPUT);
    
    digitalWrite(FIRST_BIT,LOW);
    digitalWrite(SECOND_BIT,LOW);
    digitalWrite(THIRD_BIT,LOW);
    digitalWrite(PRESENT_PIN,LOW);
    
    *buffer = *empty;
}

void loop() {
  
  ifCorrect();  
    // Look for new cards

  
    mfrc522.PCD_Init(); // Se reinician los registros lo cual causaba el problema de tarjeta Presente/ausente
    

    if ( ! mfrc522.PICC_IsNewCardPresent()){
        digitalWrite(PRESENT_PIN,LOW);
        digitalWrite(FIRST_BIT,LOW);
        digitalWrite(SECOND_BIT,LOW);
        digitalWrite(THIRD_BIT,LOW);
        statusval[0] = 0;
        Serial.println("Present FALSE");
        
        *buffer = *empty;
        return;
       
    }

    digitalWrite(PRESENT_PIN,HIGH);
    statusval[0] = 1;
    printStatus();
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
int compareAll(){
  for(int i= 0; i < sizeof(allTags); i++){
    if(compareByte(buffer,allTags[i])){
      return i;
    }
  }
  return 99;
}
void ifCorrect(){
  if(compareByte(buffer,value)){
    digitalWrite(FIRST_BIT,HIGH);
    digitalWrite(SECOND_BIT,HIGH);
    digitalWrite(THIRD_BIT,HIGH);
    setStatus(1,1,1);
  } 
  else {
    anyOtherTag();
  }
}

void anyOtherTag(){
  int selected = compareAll();
  if(selected != 99){
     
    switch (selected) {
      case 0:
        //Mandar la informacion de DO
        digitalWrite(FIRST_BIT,LOW);
        digitalWrite(SECOND_BIT,LOW);
        digitalWrite(THIRD_BIT,LOW);
        setStatus(0,0,0);
        break;
      case 1:
        //Mandar la informacion de RE
        digitalWrite(FIRST_BIT,LOW);
        digitalWrite(SECOND_BIT,LOW);
        digitalWrite(THIRD_BIT,HIGH);
        setStatus(0,0,1);
        break;
      case 2:
        //Mandar la informacion de MI
        digitalWrite(FIRST_BIT,LOW);
        digitalWrite(SECOND_BIT,HIGH);
        digitalWrite(THIRD_BIT,LOW);
        setStatus(0,1,0);
        break;
      case 3:
        //Mandar la informacion de FA
        digitalWrite(FIRST_BIT,LOW);
        digitalWrite(SECOND_BIT,HIGH);
        digitalWrite(THIRD_BIT,HIGH);
        setStatus(0,1,1);
        break;
      case 4:
        //Mandar la informacion de SOL
        digitalWrite(FIRST_BIT,HIGH);
        digitalWrite(SECOND_BIT,LOW);
        digitalWrite(THIRD_BIT,LOW);
        setStatus(1,0,0);
        break;
      case 5:
        //Mandar la informacion de LA
        digitalWrite(FIRST_BIT,HIGH);
        digitalWrite(SECOND_BIT,LOW);
        digitalWrite(THIRD_BIT,HIGH);
        setStatus(1,0,1);
        break;
      case 6:
        //Mandar la informacion de SI
        digitalWrite(FIRST_BIT,HIGH);
        digitalWrite(SECOND_BIT,HIGH);
        digitalWrite(THIRD_BIT,LOW);
        setStatus(1,1,0);
        break;
      
    }  
  }
}

void setStatus(int b , int c, int d){
  
  statusval[1] = b;
  statusval[2] = c;
  statusval[3] = d;
}

void printStatus(){
  Serial.println("");
  for(int i=0;i<4;i++){
    Serial.print(statusval[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

