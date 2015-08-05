/********************************************************
* Infrarrojo - Library - microelectronicos Bogota
* http://www.microelectronicos.com/shopexd.asp?id=657
* Rev 14/enero/2014
* Creada por Ing. Edison viveros Pasto Colombia
* libreria que lee el estado logico de un sensor infrarrojo
* There is an obstacle, the green indicator light on the circuit board.
* Detection distance: 2 ~ 60cm
* Detection angle: 35 °
* Comparator chip: LM393
* 3mm screw holes for easy mounting
* Dimensions: 3.1 x 1.5cm
*/


#ifndef infrarrojo_h
#define infrarrojo_h

//ESTABLE LA COMPATIBILIDAD PARA DIFERENTES TARJETAS DE ARDUINO
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

//DEFINICION DE LA CLASE QUE CONTIENE ATRIBUTOS O VARIABLES Y FUNCIONES
class infrarrojo {
  public:
   infrarrojo(int pin);//DEFINICION DEL CONSTRUCTOR CON SUS VARIABLES
   long lectura(int lec);//DEFINICION DE LA FUNCION
  private:  
   int _pin;
};
#endif
