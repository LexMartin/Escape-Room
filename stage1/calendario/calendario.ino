// PROYECTO CALENDARIO MAYA


// In this part the PIN is specified to use (PIN = number)
int CalendarCorrect = 13;
int CalendarIncorrect = 2;

int PartOne = 3;
int PartTwo = 5;
int PartThree = 7;


// for magnetic sensor
int OtherPartOne = 4;
int OtherPartTwo = 6;
int OtherPartThree = 8;


int ValPartOne = 0;
int ValPartTwo = 0;
int ValPartThree = 0;


int OtherValPartOne = 0;
int OtherValPartTwo = 0;
int OtherValPartThree = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(CalendarCorrect, OUTPUT);      
  pinMode(CalendarIncorrect, OUTPUT);   
  pinMode(PartOne, INPUT); 
  pinMode(PartTwo, INPUT); 
  pinMode(PartThree, INPUT); 
  
  pinMode(OtherPartOne, INPUT); 
  pinMode(OtherPartTwo, INPUT); 
  pinMode(OtherPartThree, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ValPartOne = digitalRead(PartOne);   
  ValPartTwo = digitalRead(PartTwo);   
  ValPartThree = digitalRead(PartThree); 
  
  
  OtherValPartOne = digitalRead(OtherPartOne);   
  OtherValPartTwo = digitalRead(OtherPartTwo);   
  OtherValPartThree = digitalRead(OtherPartThree); 
  
  if(myFunction(ValPartOne,OtherValPartOne) && myFunction(ValPartTwo,OtherValPartTwo) && myFunction(ValPartThree,OtherValPartThree)){
  digitalWrite(CalendarCorrect, HIGH);
  digitalWrite(CalendarIncorrect, LOW);
 
  }
  else{
  digitalWrite(CalendarIncorrect, HIGH);
  digitalWrite(CalendarCorrect, LOW);
  
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
  
