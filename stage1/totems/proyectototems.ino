// PROYECTO TOTEMS

int EyesCorrect = 13; 
int TotemPartOne = 7;
int TotemPartTwo = 4;
int TotemPartThree = 2;
int ValTotem = 0;
int ValTotem2 = 0;
int ValTotem3 = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(EyesCorrect, OUTPUT);  
  pinMode(Incorrect, OUTPUT);    
  pinMode(TotemPartOne, INPUT); 
  pinMode(TotemPartTwo, INPUT); 
  pinMode(TotemPartThree, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ValTotem = digitalRead(TotemPartOne);   
  ValTotem2 = digitalRead(TotemPartTwo);   
  ValTotem3 = digitalRead(TotemPartThree); 
  
  if(ValTotem == HIGH && ValTotem2 == HIGH && ValTotem3  == HIGH){
  digitalWrite(EyesCorrect, HIGH);
  digitalWrite(Incorrect, LOW);
  
  }
  else{
  digitalWrite(Incorrect, HIGH);
  digitalWrite(EyesCorrect, LOW);

  
  }
  
  
  
}
