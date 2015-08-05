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

//ESTABLE LA COMPATIBILIDAD PARA DIFERENTES TARJETAS DE ARDUINO
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "infrarrojo.h"
//ETAPA DE DEFINICION DE ENTRADAS Y SALIDAS ESTILO SETUP
infrarrojo::infrarrojo(int pin)
{
  pinMode(pin, INPUT);  //CONFIGURACION DEL PIN DE LECTURA
  _pin = pin;
}
long infrarrojo::lectura(int lec)//LA FUNCION REGRESA UN VALOR TIPO LONG
{
	if(digitalRead(_pin)==HIGH)//DETECTA SI EL PIN ESTA EN ESTADO ALTO O BAJO
	{
      lec = 1;
		  return lec;//RETORNA LEC CON EL VALOR DE UNO
	}
	else
	{
	  lec = 0;
	  return lec;
	}
}
