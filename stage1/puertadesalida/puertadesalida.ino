//PROYECTO PUERTA DE SALIDA

int CorrectPoints = 13;
int NoCorrectPoints = 2;

int PointOne = 3;
int PointTwo = 5;
int PointThree = 7;
int PointFour = 9;


int OtherPointOne = 4;
int OtherPointTwo = 6;
int OtherPointThree = 8;
int OtherPointFour = 10;


int OtherValPointOne = 0;
int OtherValPointTwo = 0;
int OtherValPointThree = 0;
int OtherValPointFour = 0;


int ValPointOne = 0;
int ValPointTwo = 0;
int ValPointThree = 0;
int ValPointFour = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(CorrectPoints, OUTPUT);      
  pinMode(NoCorrectPoints, OUTPUT);  
  pinMode(PointOne, INPUT); 
  pinMode(PointTwo, INPUT); 
  pinMode(PointThree, INPUT); 
  pinMode(PointFour, INPUT);
  
  
  pinMode(OtherPointOne, INPUT); 
  pinMode(OtherPointTwo, INPUT); 
  pinMode(OtherPointThree, INPUT); 
  pinMode(OtherPointFour, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ValPointOne = digitalRead(PointOne);   
  ValPointTwo = digitalRead(PointTwo);   
  ValPointThree = digitalRead(PointThree); 
  ValPointFour = digitalRead(PointFour); 
  
  
  OtherValPointOne = digitalRead(OtherPointOne);   
  OtherValPointTwo = digitalRead(OtherPointTwo);   
  OtherValPointThree = digitalRead(OtherPointThree); 
  OtherValPointFour = digitalRead(OtherPointFour); 
  
  
  if(myFunction(ValPointOne,OtherValPointOne) && myFunction(ValPointTwo,OtherValPointTwo) && myFunction(ValPointThree,OtherValPointThree) && myFunction(ValPointFour,OtherValPointFour) ){
  digitalWrite(CorrectPoints, HIGH);
  digitalWrite(NoCorrectPoints, LOW);
  
  }
  else{
  digitalWrite(NoCorrectPoints, HIGH);
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
  
