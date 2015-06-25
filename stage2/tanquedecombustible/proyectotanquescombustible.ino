// LOS TANQUES DE COMBUSTIBLE


int FullTank = 13; 
int NoFullTank = 3;
int BallGolf = 7;
int ValBallGolf = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(FullTank, OUTPUT);  
  pinMode(NoFullTank, OUTPUT);  
  pinMode(BallGolf, INPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
  ValBallGolf = digitalRead(BallGolf);   

  
  if(ValBallGolf == HIGH){
  digitalWrite(FullTank, HIGH);
  digitalWrite(NoFullTank, LOW);
  
  }
  else{
  digitalWrite(Incorrect, HIGH);
  digitalWrite(NoFullTank, LOW);

  
  }
  
  
  
}
