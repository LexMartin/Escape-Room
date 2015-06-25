// PROYECTO CALENDARIO MAYA

int CalendarCorrect = 13;
int CalendarIncorrect = 3;
int PartOne = 7;
int PartTwo = 4;
int PartThree = 2;
int ValPartOne = 0;
int ValPartTwo = 0;
int ValPartThree = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(CalendarCorrect, OUTPUT);      
  pinMode(CalendarIncorrect, OUTPUT);   
  pinMode(PartOne, INPUT); 
  pinMode(PartTwo, INPUT); 
  pinMode(PartThree, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ValPartOne = digitalRead(PartOne);   
  ValPartTwo = digitalRead(PartTwo);   
  ValPartThree = digitalRead(PartThree); 
  
  if(ValPartOne == HIGH && ValPartTwo == HIGH && ValPartThree  == HIGH){
  digitalWrite(CalendarCorrect, HIGH);
  digitalWrite(CalendarIncorrect, LOW);
 
  }
  else{
  digitalWrite(CalendarIncorrect, HIGH);
  digitalWrite(CalendarCorrect, LOW);
  
  }
  
  
  
}
