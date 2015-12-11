int correctoRFID = 2;

int ledPin = 3;

int ledPins[] = {4,5,6,7,8};
int bottons[] = {9,10,11,12};

int i;
int x;
int timer = 1000;
int timer2 = 10000;
int variable = 0;

void setup(){
 
  pinMode(correctoRFID, INPUT);
  pinMode(ledPin,OUTPUT);
  for (i=0; i <5;i++){
    pinMode(ledPins[i],OUTPUT);
    
  }
  
  Serial.begin(9600); 



}

void loop(){
  variable = digitalRead(correctoRFID);
  
  if (variable == HIGH){
    digitalWrite(ledPin, HIGH); // indicacion q es correctoRFID
    for (i=0; i <5;i++){
      digitalWrite(ledPins[i],HIGH);
    }
      delay(timer);
        Serial.println("tiempo");
    for (i=5; i>=0;i--){
      digitalWrite(ledPins[i],LOW);
      }
     delay(timer2);  
     digitalWrite(ledPin, LOW);
     Serial.println("tiempo2");
     delay(timer2); 
     
     for(x=0;x<5;x++){
       leerbotones(bottons[x]);
     
     }
  
  }else{
    digitalWrite(ledPin, LOW); 
    for (i=0; i <5;i++){
      digitalWrite(ledPins[i],LOW);
     }
  
  }


}

int leerbotones(bottons[i]){
  for(i=0;i<5;i++){
    if(digitalRead(bottons[i]) == 1){
        Serial.println("leer 1");

    
    
    }else{
      leerbotones(bottons[i]);
    
    }
  
  }
  
  
  
  
  
}
/*
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;

int old_val = 0;
int state = 0;
// the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && old_val == LOW) {
    // turn LED on:
    state = 1 -state;
    delay(10);
  }
  old_val = buttonState;
  if (state == 1){
  digitalWrite(ledPin, HIGH);
  
  }else{
  digitalWrite(ledPin,LOW);
  }


}
 
 
 */
