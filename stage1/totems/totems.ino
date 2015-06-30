// PROYECTO TOTEMS
//  Created by Cindy Canul Canul
// E-mail: cindycanul92@gmail.com



// In this part the PIN is specified to use (PIN = number)
int EyesCorrect = 13; 
int Incorrect = 2;
int TotemPartOne = 5;
int TotemPartTwo = 3;
int TotemPartThree = 7;


// for magnetic sensor
int OtherTotemPartOne = 4;
int OtherTotemPartTwo = 6;
int OtherTotemPartThree = 8;



int ValTotem = 0;
int ValTotem2 = 0;
int ValTotem3 = 0;

int OtherValTotem = 0;
int OtherValTotem2 = 0;
int OtherValTotem3 = 0;



// INPUTS AND OUTPUTS
void setup() {
  // put your setup code here, to run once:
  pinMode(EyesCorrect, OUTPUT);  
  pinMode(Incorrect, OUTPUT);    
  pinMode(TotemPartOne, INPUT); 
  pinMode(TotemPartTwo, INPUT); 
  pinMode(TotemPartThree, INPUT); 
  
  pinMode(OtherTotemPartOne, INPUT); 
  pinMode(OtherTotemPartTwo, INPUT); 
  pinMode(OtherTotemPartThree, INPUT); 
}



// put your main code here, to run repeatedly:
void loop() {
  
  ValTotem = digitalRead(TotemPartOne);   
  ValTotem2 = digitalRead(TotemPartTwo);   
  ValTotem3 = digitalRead(TotemPartThree); 
  
  
  OtherValTotem = digitalRead(OtherTotemPartOne);   
  OtherValTotem2 = digitalRead(OtherTotemPartTwo);   
  OtherValTotem3 = digitalRead(OtherTotemPartThree); 
  
 
  if(myFunction(ValTotem,OtherValTotem) && myFunction(ValTotem2,OtherValTotem2) && myFunction(ValTotem3,OtherValTotem3)){
  digitalWrite(EyesCorrect, HIGH);
  digitalWrite(Incorrect, LOW);
  
  }
  else{
  digitalWrite(Incorrect, HIGH);
  digitalWrite(EyesCorrect, LOW);

  
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
  
  
  
  

