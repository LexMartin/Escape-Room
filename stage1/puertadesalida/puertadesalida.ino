//PROYECTO PUERTA DE SALIDA

int 4CorrectPoints = 13;
int 4NoCorrectPoints = 3;
int PointOne = 7;
int PointTwo = 4;
int PointThree = 2;
int PointFour = 5;
int ValPointOne = 0;
int ValPointTwo = 0;
int ValPointThree = 0;
int ValPointFour = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(4CorrectPoints, OUTPUT);      
  pinMode(4NoCorrectPoints, OUTPUT);  
  pinMode(PointOne, INPUT); 
  pinMode(PointTwo, INPUT); 
  pinMode(PointThree, INPUT); 
   pinMode(PointFour, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ValPointOne = digitalRead(PointOne);   
  ValPointTwo = digitalRead(PointTwo);   
  ValPointThree = digitalRead(PointThree); 
  ValPointFour = digitalRead(PointFour); 
  
  if(ValPointOne == HIGH && ValPointTwo == HIGH && ValPointThree  == HIGH && ValPointFour  == HIGH){
  digitalWrite(4CorrectPoints, HIGH);
  digitalWrite(4NoCorrectPoints, LOW);
  
  }
  else{
  digitalWrite(4NoCorrectPoints, HIGH);
  digitalWrite(4CorrectPoints, LOW);
  
  }
  
  
  
}
