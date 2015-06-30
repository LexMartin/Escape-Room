// PROYECTO CERRADURA DE 3 ANILLOS
//  Created by Cindy Canul Canul
// E-mail: cindycanul92@gmail.com

//limite de entradas del arduino

int NumbersCorrect = 13; 
int NumbersIncorrect = 2;


int NumberOne = 3;
int NumberTwo = 5;
int NumberThree = 7;
int NumberFour = 9;
int NumberFive = 11;
int NumberSix = 13;
int NumberSeven = 15;
int NumberEight = 17;
int NumberNine = 19;
int NumberTen = 21;


int OtherNumberOne = 4;
int OtherNumberTwo = 6;
int OtherNumberThree = 8;
int OtherNumberFour = 10;
int OtherNumberFive = 12;
int OtherNumberSix = 14;
int OtherNumberSeven = 16;
int OtherNumberEight = 18;
int OtherNumberNine = 20;
int OtherNumberTen = 22;


int variable1 = 0;
int variable2 = 0;
int variable3 = 0;
int variable4 = 0;
int variable5 = 0;
int variable6 = 0;
int variable7 = 0;
int variable8 = 0;
int variable9 = 0;
int variable10 = 0;

int variable11 = 0;
int variable12 = 0;
int variable13 = 0;
int variable14 = 0;
int variable15 = 0;
int variable16 = 0;
int variable17 = 0;
int variable18 = 0;
int variable19 = 0;
int variable20 = 0;


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

  variable1 = digitalRead(NumberOne); 
  variable2 = digitalRead(NumberTwo); 
  variable3 = digitalRead(NumberThree); 
  variable4 = digitalRead(NumberFour); 
  variable5 = digitalRead(NumberFive); 
  variable6 = digitalRead(NumberSix); 
  variable7 = digitalRead(NumberSeven); 
  variable8 = digitalRead(NumberEight); 
  variable9 = digitalRead(NumberNine); 
  variable10 = digitalRead(NumberTen); 
  
  variable11 = digitalRead(OtherNumberOne); 
  variable12 = digitalRead(OtherNumberTwo); 
  variable13 = digitalRead(OtherNumberThree); 
  variable14 = digitalRead(OtherNumberFour); 
  variable15 = digitalRead(OtherNumberFive); 
  variable16 = digitalRead(OtherNumberSix); 
  variable17 = digitalRead(OtherNumberSeven); 
  variable18 = digitalRead(OtherNumberEight); 
  variable19 = digitalRead(OtherNumberNine); 
  variable20 = digitalRead(OtherNumberTen); 



  
  if(myFunction(NumberOne,OtherNumberOne) && myFunction(NumberTwo,OtherNumberTwo) && myFunction(NumberThree,OtherNumberThree) && myFunction(NumberFour,OtherNumberFour) && myFunction(NumberFive,OtherNumberFive) && 
  myFunction(NumberSix,OtherNumberSix) && myFunction(NumberSeven,OtherNumberSeven) && myFunction(NumberEight,OtherNumberEight) && myFunction(NumberNine,OtherNumberNine) && myFunction(NumberTen,OtherNumberTen)  ){
  digitalWrite(NumbersCorrect, HIGH);
  digitalWrite(NumbersIncorrect, LOW);
  
  }
  else{
  digitalWrite(NumbersIncorrect, HIGH);
  digitalWrite(NumbersCorrect, LOW);

  
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
