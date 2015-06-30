// DISCOS MAGNETICOS
//  Created by Cindy Canul Canul
// E-mail: cindycanul92@gmail.com


int CorrectPoints = 13; 
int IncorrectPoints = 2;

int PointOne = 3;
int PointTwo = 5;
int PointThree = 7;
int PointFour = 9;
int PointFive = 11;
int PointFix = 14;
int PointSeven = 16;
int PointEight = 18;

int OtherPointOne = 4;
int OtherPointTwo = 6;
int OtherPointThree = 8;
int OtherPointFour = 10;
int OtherPointFive = 12;
int OtherPointFix = 15;
int OtherPointSeven = 17;
int OtherPointEight = 19;

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


void setup() {
  // put your setup code here, to run once:
  pinMode(CorrectPoints, OUTPUT);  
  pinMode(IncorrectPoints, OUTPUT);  
  pinMode(PointOne, INPUT); 
  pinMode(PointTwo, INPUT); 
  pinMode(PointThree, INPUT); 
  pinMode(PointFour, INPUT); 
  pinMode(PointFive, INPUT); 
  pinMode(PointFix, INPUT); 
  pinMode(PointSeven, INPUT); 
  pinMode(PointEight, INPUT); 
  
  pinMode(OtherPointOne, INPUT); 
  pinMode(OtherPointTwo, INPUT); 
  pinMode(OtherPointThree, INPUT); 
  pinMode(OtherPointFour, INPUT); 
  pinMode(OtherPointFive, INPUT); 
  pinMode(OtherPointFix, INPUT); 
  pinMode(OtherPointSeven, INPUT); 
  pinMode(OtherPointEight, INPUT); 
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  variable1 = digitalRead(PointOne); 
  variable2 = digitalRead(PointTwo); 
  variable3 = digitalRead(PointThree); 
  variable4 = digitalRead(PointFour); 
  variable5 = digitalRead(PointFive); 
  variable6 = digitalRead(PointFix); 
  variable7 = digitalRead(PointSeven); 
  variable8 = digitalRead(PointEight); 
  
  variable9 = digitalRead(OtherPointOne); 
  variable10 = digitalRead(OtherPointTwo); 
  variable11 = digitalRead(OtherPointThree); 
  variable12 = digitalRead(OtherPointFour); 
  variable13 = digitalRead(OtherPointFive); 
  variable14 = digitalRead(OtherPointFix); 
  variable15 = digitalRead(OtherPointSeven); 
  variable16 = digitalRead(OtherPointEight); 
  


  


  
  if(myFunction(PointOne,OtherPointOne) && myFunction(PointTwo,OtherPointTwo) && myFunction(PointThree,OtherPointThree) && myFunction(PointFour,OtherPointFour) 
  && myFunction(PointFive,OtherPointFive) && myFunction(PointFix,OtherPointFix) && myFunction(PointSeven,OtherPointSeven) && myFunction(PointEight,OtherPointEight)){
  digitalWrite(CorrectPoints, HIGH);
  digitalWrite(IncorrectPoints, LOW);
  
  }
  else{
  digitalWrite(IncorrectPoints, HIGH);
  digitalWrite(CorrectPoints, LOW);

  
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
