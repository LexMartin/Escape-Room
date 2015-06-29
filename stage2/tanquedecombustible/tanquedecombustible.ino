// LOS TANQUES DE COMBUSTIBLE


int FullTank = 13; 
int NoFullTank = 2;

int BallGolf = 3;
int OtherBallGolf = 4;


int ValBallGolf = 0;
int OtherValBallGolf = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(FullTank, OUTPUT);  
  pinMode(NoFullTank, OUTPUT);  
  pinMode(BallGolf, INPUT); 
  pinMode(OtherBallGolf, INPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  ValBallGolf = digitalRead(BallGolf);   
  OtherValBallGolf = digitalRead(OtherBallGolf);  

  
  if(myFunction(ValBallGolf,OtherValBallGolf)){
  digitalWrite(FullTank, HIGH);
  digitalWrite(NoFullTank, LOW);
  
  }
  else{
  digitalWrite(NoFullTank, HIGH);
  digitalWrite(FullTank, LOW);

  
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
