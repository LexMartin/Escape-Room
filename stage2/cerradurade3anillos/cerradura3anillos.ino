// PROYECTO CERRADURA DE 3 ANILLOS


//limite de entradas del arduino

int NumbersCorrect = 13; 
int NumbersIncorrect = 3;
int NumberOne = 2;
int NumberTwo = 6;
int NumberThree = 4;
int NumberFour = 5;
int NumberFive = 7;
int NumberSix = 8;
int NumberSeven = 9;
int NumberEight = 10;
int NumberNine = 11;
int NumberTen = 12;


void setup() {
  // put your setup code here, to run once:
  pinMode(NumbersCorrect, OUTPUT);  
  pinMode(NumbersIncorrect, OUTPUT);    
  pinMode(NumberOne, INPUT); 
  pinMode(NumberTwo, INPUT); 
  pinMode(NumberThree, INPUT); 
  pinMode(NumberFour, INPUT); 
  pinMode(NumberFive, INPUT); 
  pinMode(NumberSix, INPUT); 
  pinMode(NumberSeven, INPUT); 
  pinMode(NumberEight, INPUT); 
  pinMode(NumberNine, INPUT); 
  pinMode(NumberTen, INPUT); 
}



void loop() {
  // put your main code here, to run repeatedly:

  
  if(NumberOne == HIGH && NumberTwo == HIGH && NumberThree  == HIGH && NumberFour == HIGH && NumberFive == HIGH && NumberSix  == HIGH && NumberSeven == HIGH && NumberEight == HIGH && NumberNine  == HIGH && NumberTen == HIGH){
  digitalWrite(NumbersCorrect, HIGH);
  digitalWrite(NumbersIncorrect, LOW);
  
  }
  else{
  digitalWrite(NumbersIncorrect, HIGH);
  digitalWrite(NumbersCorrect, LOW);

  
  }
  
  
  
}
