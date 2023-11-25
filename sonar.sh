#!/bin/bash
currentAngle=0
signAngle=0

#INICIAMOS UN FOR PARA REALIZAR 2 BARRIDOS
for (( itr=0; itr<37; itr++ ))
do
    #CORREMOS EL .C PARA MOVER EL SERVO Y MEDIR LA DISTANCIA
    /home/juanfelipe/Documentos/proyectoFinal/test/readSensors $currentAngle
    #SUBIMOS LOS DATOS A THINGSPEAK
    python3  /home/juanfelipe/Documentos/proyectoFinal/test/lectura_python.py
    #VERIFICAMOS SI LA DIRECCIÓN DEL ÁNGULO ES POSITIVA O NEGATIVA
    #Y SUMAMOS O RESTAMOS DEPENDIENDO DE ELLO
    if [ $signAngle -eq 0 ]
    then
	let currentAngle=$currentAngle+10
    else
	let currentAngle=$currentAngle-10
    fi

    #VERIFICAMOS SI ES MOMENTO DE CAMBIAR EL SIGNO DEL ÁNGULO
    #QUE OCURRE CUANDO TERMINA EL PRIMER BARRIDO POSITIVO
    if [ $itr -ge 17 ]
    then
	signAngle=1
    else
	signAngle=0
    fi
done
