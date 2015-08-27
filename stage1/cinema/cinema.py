#! /usr/bin/python
import RPi.GPIO as GPIO # LIBRERIA NECESARIA PARA INTERACTUAR CON LA LOS PINES DE LA RASPBERRY
import time # TIEMPO
import subprocess # 


#Automatizacion -  CINEMA
#Created by Cindy Canul Canul & Cristian Kumul Uc
#E-mail: cindycanul92@gmail.com, cristiankumul@gmail.com


GPIO.setmode(GPIO.BOARD) # Especificacion de modo de los pines, en este caso: BOARD
#PIO.setmode(GPIO.BCM) # Se puede usar, pero es necesario cambiar el numero de PIN, verificar en el esquema
GPIO.setwarnings(False) # Necesario para los warnings


################# SALIDAS   ######################
#GPIO.SETUP (<NUMERO DE PIN>,GPIO.<SALIDA O ENTRADA>)


GPIO.setup(12, GPIO.OUT)# para la vibracion de mascaras
GPIO.setup(7, GPIO.OUT) # luz
GPIO.setup(18,GPIO.OUT)# ventana que se va abrir
GPIO.setup(11, GPIO.OUT) # ojos de las mascaras
GPIO.setup(22, GPIO.OUT)# pantalla para la reproduccion del video

################# ENTRADAS ####################

GPIO.setup(13, GPIO.IN) #MASCARA UNO
GPIO.setup(15, GPIO.IN) #MASCARA DOS
GPIO.setup(16, GPIO.IN) #MASCARA TRES

variable = True

def secuencia(value):
    if(value and variable):
    
	#print("MASCARAS CORRECTAS - JUEGO CORRECTO")
	#print("VIBRACION DE LAS MASCARAS")
    
    # PUNTO UNO:
        GPIO.output(12, True) # vibrador
        time.sleep(2) # 2 segundos
    
    #PUNTO DOS:
	   #print("APAGANDO LUZ")
        GPIO.output(7, False) # se apaga la luz

    #PUNTO TRES: 
        #print("ABRIR VENTANA")
        GPIO.output(18, True)
        time.sleep(5) # Asignar el tiempo (en segundos) dependiendo de lo q tarde en abrir la ventana

    #PUNTO CUATRO:
	#print("ENCENDER OJOS DE MASCARAS")
        GPIO.output(11, True) # para el encedido de los ojos de la mascaras
        time.sleep(5) #asignar un tiempo deseado
	
    #PUNTO CINCO:

    #print("ENCENDER PANTALLA")
        GPIO.output(22, True)  # encendido de la pantalla 
        time.sleep(5) #asignar tiempo de acuerdo al encendido de la pantalla
        

        #print("EMPIEZA VIDEO")
     ### REPRODUCCION DEL VIDEO   
     #### PONER EL VIDEO EN LA MISMA CARPETA QUE EL PROGRAMA (cinema.py)
     # myprocess = subprocess.Popen(['omxplayer','NOMBRE DEL VIDEO.mp4'])
     # asignar NOMBRE DEL VIDEO y el FORMATO

        myprocess = subprocess.Popen(['omxplayer','videomuestra.mp4'])

        time.sleep(110)# PONGA LA DURACION DEL VIDEO (EN SEGUNDOS)+ tiempo extra (aprox. 10 segundos)
       

    ###### CUANDO FINALIZA EL VIDEO
    ## ASIGNAR EL TIEMPO DESEADO EN time.sleep(TIEMPO EN SEGUNDOS)
    	#print("ENCENDER LUCES")
    	GPIO.output(7, True)
    	#print("APAGAR PANTALLAZA")
    	GPIO.output(22, False)
    	time.sleep(5)
    	#print("apagar ojos")
    	GPIO.output(11,False)
        time.sleep(5)
    	#print("cierra ventana")
    	GPIO.output(18,False)
    	#print("vibracion")
    	GPIO.output(12, False)
	
        
    else:
        #GPIO.output(11, False)
        #LUZ ENCENDIDA
        GPIO.output(7, True)

        

def checkStatus():
    #verificar las tres mascaras
    if (GPIO.input(13) == True and GPIO.input(15) == True and GPIO.input(16) == True):
        return True
    else:
        if (GPIO.input(13) == False and GPIO.input(15) == False and GPIO.input(16) == False):
            varible = True
        return False
    

   
while True:
    GPIO.output(7, True) # Luz encendida
    GPIO.output(12,False) # vibrador apagado
    GPIO.output(18, False)# ventana que se va abrir apagado
    GPIO.output(11, False) # ojos de las mascaras apagado
    GPIO.output(22, False)# pantalla apagado


    # verificar el estado actual - mascaras
    if(checkStatus()):
        #funcion secuencia
        secuencia(True)
        variable=True
                          
    else:
        secuencia(False)


         
