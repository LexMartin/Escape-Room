// PROYECTO SARCOFAGO


int KeyCorrect = 13; 
int KeyIncorrect = 3;
int KeyYellow = 7;
int KeyOrange = 4;
int KeyRed = 2;
int ValKeyYellow = 0;
int ValKeyOrange = 0;
int ValKeyRed = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(KeyCorrect, OUTPUT);  
  pinMode(KeyIncorrect, OUTPUT);    
  pinMode(KeyYellow, INPUT); 
  pinMode(KeyOrange, INPUT); 
  pinMode(KeyRed, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ValKeyYellow = digitalRead(KeyYellow);   
  ValKeyOrange = digitalRead(KeyOrange);   
  ValKeyRed = digitalRead(KeyRed); 
  
  if(ValKeyYellow == HIGH && ValKeyOrange == HIGH && ValKeyRed  == HIGH){
  digitalWrite(KeyCorrect, HIGH);
  digitalWrite(KeyIncorrect, LOW);
  
  }
  else{
  digitalWrite(KeyIncorrect, HIGH);
  digitalWrite(KeyCorrect, LOW);

  
  }
  
  
  
}
