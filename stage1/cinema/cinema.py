#! /usr/bin/python

#import RPi.GPIO as GPIO # LIBRERIA NECESARIA PARA INTERACTUAR CON LA LOS PINES DE LA RASPBERRY

import time # TIEMPO
import subprocess #
import wiringpi2

io = wiringpi2.GPIO(wiringpi2.GPIO.WPI_MODE_PINS) #PINS MODO WIRINGS
# VER EL DIAGRAMA PARA LA COLOCACION DE PINES


#Automatizacion -  CINEMA
#Created by Cindy Canul Canul & Cristian Kumul Uc
#E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com

#MATERIAL
# 1 RASPBERRY MODEL B
# 6 SENSORES HALL
# 3 RELAY
# 7 LEDS  

# CABLES
#NUMERO DE CABLES | NUMERO DE HILOS
#       3                   3           PARA RELAYS
#       7                   2           PARA LEDS
#       6                   3           PARA SENSORES HALL


# CABLES PARA LAS CONEXIONES DE RASPBERRY Y RELAYS


# LA ESPECIFICACION DE LOS PINES ESTA EN LA IMAGEN: raspberry.png



################# ENTRADAS   ######################
io.pinMode(8,io.INPUT) #MASCARA UNO
io.pinMode(9,io.INPUT) #MASCARA DOS
io.pinMode(7,io.INPUT) #MASCARA TRES


io.pinMode(15,io.INPUT) #MASCARA UNO - RESPALDO
io.pinMode(16,io.INPUT) #MASCARA DOS - RESPALDO
io.pinMode(1,io.INPUT) #MASCARA TRES - RESPALDO

################# SALIDAS   ######################


io.pinMode(0,io.OUTPUT) #vibrador de mascaras uno
io.pinMode(2,io.OUTPUT) #vibrador de mascaras dos
io.pinMode(3,io.OUTPUT) #vibrador de mascaras tres

io.pinMode(4,io.OUTPUT) #luz

io.pinMode(5,io.OUTPUT) #ventana que se abre

io.pinMode(12,io.OUTPUT) #ojos
io.pinMode(13,io.OUTPUT) #ojos

io.pinMode(14,io.OUTPUT) #pantalla para el video


variable = True

def secuencia(value):
    if(value and variable):
    
    #print("MASCARAS CORRECTAS - JUEGO CORRECTO")
    #print("VIBRACION DE LAS MASCARAS")
    
    # PUNTO UNO:
        io.digitalWrite(0,io.HIGH)
        io.digitalWrite(2,io.HIGH)
        io.digitalWrite(3,io.HIGH)# vibrador
        time.sleep(2) # 2 segundos
    
    #PUNTO DOS:
       #print("APAGANDO LUZ")
        io.digitalWrite(4,io.LOW) # se apaga la luz

    #PUNTO TRES: 
        #print("ABRIR VENTANA")
        io.digitalWrite(5,io.HIGH)
    
        time.sleep(5) # Asignar el tiempo (en segundos) dependiendo de lo q tarde en abrir la ventana

    #PUNTO CUATRO:
    #print("ENCENDER OJOS DE MASCARAS")
        io.digitalWrite(12,io.HIGH) # para el encedido de los ojos de la mascaras
        io.digitalWrite(13,io.HIGH)
        time.sleep(5) #asignar un tiempo deseado
    
    #PUNTO CINCO:

    #print("ENCENDER PANTALLA")
        io.digitalWrite(14,io.HIGH)  # encendido de la pantalla 
        time.sleep(5) #asignar tiempo de acuerdo al encendido de la pantalla
        

        #print("EMPIEZA VIDEO")
     ### REPRODUCCION DEL VIDEO   
     #### PONER EL VIDEO EN LA MISMA CARPETA QUE EL PROGRAMA (cinema.py)
     # myprocess = subprocess.Popen(['omxplayer','NOMBRE DEL VIDEO.mp4'])
     # asignar NOMBRE DEL VIDEO y el FORMATO

        myprocess = subprocess.Popen(['omxplayer','videomuestra.mp4'])

        time.sleep(65)# PONGA LA DURACION DEL VIDEO (EN SEGUNDOS)+ tiempo extra (aprox. 10 segundos)
       

    ###### CUANDO FINALIZA EL VIDEO
    ## ASIGNAR EL TIEMPO DESEADO EN time.sleep(TIEMPO EN SEGUNDOS)
        #print("ENCENDER LUCES")
        io.digitalWrite(4,io.HIGH)
        #print("APAGAR PANTALLA")
        io.digitalWrite(14,io.LOW)
        time.sleep(5)
        #print("apagar ojos")
        io.digitalWrite(12,io.LOW) 
        io.digitalWrite(13,io.LOW)
        time.sleep(5)
        #print("cierra ventana")
        io.digitalWrite(5,io.LOW)
        #print("vibracion")
        io.digitalWrite(0,io.LOW)
        io.digitalWrite(2,io.LOW)
        io.digitalWrite(3,io.LOW)
    
        
    else:
        #GPIO.output(11, False)
        #LUZ ENCENDIDA
        io.digitalWrite(4,io.HIGH)

        

def checkStatus():
    #verificar las tres mascaras

    
        
    
    if (io.digitalRead(8) == io.HIGH or io.digitalRead(15) == io.HIGH )and (io.digitalRead(9) == io.HIGH or io.digitalRead(16) == io.HIGH ) and (io.digitalRead(7) == io.HIGH or io.digitalRead(1) == io.HIGH ):
        return True
    else:
        if ((io.digitalRead(8) == io.LOW or io.digitalRead(15) == io.LOW )and (io.digitalRead(9) == io.LOW or io.digitalRead(16) == io.LOW ) and (io.digitalRead(7) == io.LOW or io.digitalRead(1) == io.LOW )):
            varible = True
            return False
    


   
while True:
    io.digitalWrite(4,io.HIGH) # Luz encendida
    io.digitalWrite(0,io.LOW)
    io.digitalWrite(2,io.LOW)
    io.digitalWrite(3,io.LOW)# vibrador apagado
    
    io.digitalWrite(5,io.LOW)# ventana que se va abrir apagado
 
    io.digitalWrite(12,io.LOW) 
    io.digitalWrite(13,io.LOW) # ojos de las mascaras apagado
    
    io.digitalWrite(14,io.LOW)# pantalla apagado

    io.digitalRead(8)
    io.digitalRead(9)
    io.digitalRead(7)

    io.digitalRead(15)
    io.digitalRead(16)
    io.digitalRead(1)

    # verificar el estado actual - mascaras
    if(checkStatus()):
        #funcion secuencia
        secuencia(True)
        variable=True
                          
    else:
        secuencia(False)
