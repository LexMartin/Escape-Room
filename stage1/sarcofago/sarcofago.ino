// PROYECTO SARCOFAGO

// In this part the PIN is specified to use (PIN = number)
int KeyCorrect = 13; 
int KeyIncorrect = 2;


int KeyYellow = 3;
int KeyOrange = 5;
int KeyRed = 7;

int OtherKeyYellow = 4;
int OtherKeyOrange = 6;
int OtherKeyRed = 8;

int ValKeyYellow = 0;
int ValKeyOrange = 0;
int ValKeyRed = 0;


int OtherValKeyYellow = 0;
int OtherValKeyOrange = 0;
int OtherValKeyRed = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(KeyCorrect, OUTPUT);  
  pinMode(KeyIncorrect, OUTPUT);    
  pinMode(KeyYellow, INPUT); 
  pinMode(KeyOrange, INPUT); 
  pinMode(KeyRed, INPUT); 
  pinMode(OtherKeyYellow, INPUT); 
  pinMode(OtherKeyOrange, INPUT); 
  pinMode(OtherKeyRed, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ValKeyYellow = digitalRead(KeyYellow);   
  ValKeyOrange = digitalRead(KeyOrange);   
  ValKeyRed = digitalRead(KeyRed); 
  
  OtherValKeyYellow = digitalRead(OtherKeyYellow);   
  OtherValKeyOrange = digitalRead(OtherKeyOrange);   
  OtherValKeyRed = digitalRead(OtherKeyRed); 
  
  if(myFunction(ValKeyYellow,OtherValKeyYellow) && myFunction(ValKeyOrange,OtherValKeyOrange) && myFunction(ValKeyRed,OtherValKeyRed) ){
  digitalWrite(KeyCorrect, HIGH);
  digitalWrite(KeyIncorrect, LOW);
  
  }
  else{
  digitalWrite(KeyIncorrect, HIGH);
  digitalWrite(KeyCorrect, LOW);

  
  }
  
  
  
}


 // THIS FUNCTION IS FOR magnetic sensor
  bool myFunction(int x, int y){
  if (x == HIGH || y == HIGH){
  return true;
  }
  
  else{
   return false;
  }
  
  
  } // bool
  
