
/************************************************************************
* PROGRAMA EJEMPLO PARA LEER EL ESTADO LOGICO 0 O 1 DEL SENSOR INFRARROJO
* EJEMPLO CREADO POR ING EDISON V PASTO COLOMBIA
* MICROELECTRONICOS COLOMBIA 2014/ENERO
************************************************************************/
#include <infrarrojo.h>

infrarrojo estado(13);//DEFINICION DEL PIN DEL ARDUINO A USAR
int VALOR;//VARIBLE QUE RECIBE EL DATO
int led =12;//REDEFINICION DE PIN DE ARDUINO PARA LED INDICADOR DE PULSO(ESTO ES OPCIONAL)
int led_estado;//VARIABLE

//CONFIGURACION DE SETUP
void setup() {
pinMode(led,OUTPUT);//LED QUE INDICA EL ESTADO DEL LED
Serial.begin(9600); //VELOCIDAD COMUNICACION SERIAL
}
//CODIGO PRINCIPAL
void loop() {
Serial.print("\n leyendo estado sensor: \n");//IMPRIME MENSAJE EN PC
Serial.print(estado.lectura(VALOR));//IMPRIME EL ESTADO DEL Vo DEL SENSOR MEDIANTE LA VARIABLE VALOR
led_estado = estado.lectura(VALOR);//LED QUE RECOGE EL ESTADO DEL SENSOR
if(led_estado == 1)//ETAPA DE COMPARACION PARA ACTIVAR UN LED SEGUN EL ESTADO DEL SENSOR
{
  digitalWrite(led,HIGH);//PRENDE UN LED SI EL SENSOR DETECTA OBSTACULO
}
else
{
  digitalWrite(led,LOW);
}
delay(100);//GENERA UN TIEMPO PARA LEER E IMPRIMIR EN PUERTO SERIE


  
}
