#include <Wire.h>
#include <pca9555.h>

pca9555 gpio1(0x20);
pca9555 gpio2(0x25);
pca9555 gpio3(0x27);
int n_nodes = 7;
int inicial_node=0;
int nodeSelected = inicial_node;
int winGame = 0;
//Se representa el grafo con una matriz de concurrencias, la posición  6 representa el número de vecinos que posee el nodo k
int graph[24][7] = 
 {
                     {1,2,3,0,0,0,3},
                     {0,2,0,0,0,0,2},
                     {0,1,3,4,0,0,4},
                     {0,2,4,0,0,0,3},
                     {2,3,5,6,7,0,5},
                     {4,6,0,0,0,0,2},
                     {4,5,7,0,0,0,3},
                     {4,6,8,9,10,0,5},
                     {17,9,7,0,0,0,3},
                     {8,7,10,11,13,17,6},
                     {7,9,11,0,0,0,3},
                     {10,9,13,12,0,0,4},
                     {13,11,0,0,0,0,2},
                     {17,9,11,12,14,16,6},
                     {13,15,16,0,0,0,3},
                     {16,14,0,0,0,0,2},
                     {18,17,13,14,15,20,6},
                     {16,13,9,8,0,0,4},
                     {16,19,0,0,0,0,2},
                     {22,20,18,0,0,0,3},
                     {21,22,19,16,0,0,4},
                     {22,20,0,0,0,0,2},
                     {21,20,19,23,0,0,4},
                     {22,0,0,0,0,0,1},
     };
int visitedNodes[24] = {0};
void setup() {
  
  

    
    Serial.begin(38400);
    delay(100);
    gpio1.begin();//x.begin(true) will override automatic SPI initialization
    gpio2.begin();
    gpio3.begin();
    
    
    
    gpio3.gpioPinMode(OUTPUT);

    for(int i = 0; i < 16 ; i++)
    {
      if(i < 8)
      {
        gpio1.gpioPinMode(i,INPUT);
        gpio2.gpioPinMode(i,INPUT);
        gpio3.gpioPinMode(i,INPUT);
      }
      else
      {
        gpio1.gpioPinMode(i,OUTPUT);
        gpio2.gpioPinMode(i,OUTPUT);
        gpio3.gpioPinMode(i,OUTPUT);
      }
    }

    
    
  
}

void loop() {
  int j =0;
  
  int activeNeighbor;
  inicialNode();
  while(j < n_nodes)
  {
    //Serial.println("En el wuile");
    activeNeighbor = readNeighbors(graph[nodeSelected]);
    //Serial.println(activeNeighbor);
    while(activeNeighbor == 99){
        activeNeighbor = readNeighbors(graph[nodeSelected]);
      }

    if(visitedNodes[activeNeighbor] == 0)
    {
      visitedNodes[activeNeighbor] = 1;
      j++;
      nodeSelected = activeNeighbor;
      setVisitedLed(activeNeighbor,HIGH);
      
      
    }
    else
    {
      j = 0;
      error();
      
    }

    Serial.println(j);
    
  }

  winner();
  
  

}

void winner()
{
  for(int i = 0 ; i <n_nodes; i++ )
  {
    visitedNodes[i] = 0;
  }
  for(int i = 8 ; i < 16; i++ )
  {
    gpio1.gpioDigitalWrite(i,LOW);
    gpio2.gpioDigitalWrite(i,LOW);
    gpio3.gpioDigitalWrite(i,LOW);
  }

  delay(400);

  for(int i = 15 ; i > 7; i-- )
  {
    gpio1.gpioDigitalWrite(i,HIGH);
    delay(500);
    
  }
  for(int i = 15 ; i > 7; i-- )
  {
   
    gpio2.gpioDigitalWrite(i,HIGH);
    delay(500);

  }
  for(int i = 15 ; i > 7; i-- )
  {
    gpio3.gpioDigitalWrite(i,HIGH);
    delay(500);
  }
  delay(400);
  for(int i = 8 ; i < 16; i++ )
  {
    gpio1.gpioDigitalWrite(i,LOW);
    gpio2.gpioDigitalWrite(i,LOW);
    gpio3.gpioDigitalWrite(i,LOW);
  }

  
}
void error()
{
  
  for(int i = 0 ; i <n_nodes; i++ )
  {
    visitedNodes[i] = 0;
  }
  for(int i = 8 ; i < 16; i++ )
  {
    gpio1.gpioDigitalWrite(i,HIGH);
    gpio2.gpioDigitalWrite(i,HIGH);
    gpio3.gpioDigitalWrite(i,HIGH);
  }
  
  delay(1000);
  for(int i = 8 ; i < 16; i++ )
  {
    gpio1.gpioDigitalWrite(i,LOW);
    gpio2.gpioDigitalWrite(i,LOW);
    gpio3.gpioDigitalWrite(i,LOW);
  } 
  inicialNode(); 
  nodeSelected = inicial_node;
}
void inicialNode()
{
  for(int i= 0; i< 4;i++)
  {
      if(i%2 != 1){
        setVisitedLed(inicial_node,HIGH);
      }
      else{
         setVisitedLed(inicial_node,LOW);
      }
      delay(400);
    }
    setVisitedLed(inicial_node,HIGH);
    
}
  

int readNeighbors(int node[])
{
  int selected;
  //Serial.println("Leer vecinos");
  for(int i = 0; i < node[6];i++)
  {
    //Serial.print(node[i]);
    if(getHallValue(node[i]))
    {
      selected = node[i];
      return selected;
    }
    else selected = 99;
  }
  //Serial.println("Seleccionado");
  //Serial.println(selected);
  return selected;
}
bool getHallValue(int x){
    if(x < 8){
      if(gpio1.gpioDigitalRead(x)) return true;
      else return false; 
    }
    else if(x > 7 && x < 16)
    {
      if(gpio2.gpioDigitalRead(x-8)) return true;
      else return false; 
    }
    else if(x > 15 && x < 24)
    {
      if(gpio3.gpioDigitalRead(x-16)) return true;
      else return false;
    }
    
  }

  void setVisitedLed(int x, bool value)
  {
     if(x < 8){
      gpio1.gpioDigitalWrite(x+8,value);
    }
    else if(x > 7 && x < 16)
    {
      gpio2.gpioDigitalWrite(x,value);
      
    }
    else if(x > 15 && x < 24)
    {
      gpio3.gpioDigitalWrite(x-8,value);
      
    }
  
  }
