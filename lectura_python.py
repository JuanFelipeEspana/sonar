#!/usr/bin/env python3
import paho.mqtt.publish as publish
from datetime import datetime

#SE DEFINE LA RUTA DEL ARCHIVO
file_path = './data.txt'

def leer_sensores():
    try:
        with open(file_path, 'r') as file:
            #LEEMOS LA PRIMERA LÍNEA DEL ARCHIVO
            first_line = file.readline().strip()
            print(f'Se leyo: {first_line}')
            #SE SEPARAN POR COMAS
            valores = first_line.split(',')
            if len(valores) == 2:
                #OBTENEMOS LAS MEDICIONES
                grados = float(valores[0])
                longitud = float(valores[1])
                print(f"Grados: {grados}")
                print(f"Longitud: {longitud}")
                #SE DEVUELVEN LOS VALORES LEÍDOS
                return grados, longitud  
            else:
                print("Formato de línea incorrecto")
    except FileNotFoundError:
        print(f'File not found: {file_path}')
    except Exception as e:
        print(f'An error occurred: {e}')

#CONFIGURACIÓN PARA CONEXIÓN A THINGSPEAK
channel_ID = "XXXXXXX"
mqtt_host ="mqtt3.ThingSpeak.com"
api_key = "XXXXXXXXXXXXXXX"
mqtt_client_ID = "XXXXXXXXXXXXXXXXXXXXXXX"
mqtt_username =  "XXXXXXXXXXXXXXXXXXXXXXX"
mqtt_password = "XXXXXXXXXXXXXXXXXXXXXXX"
t_transport = "tcp"
t_port = 1883
topic =  "channels/" + channel_ID + "/publish" 

#ALMACENAMIENTO DE LAS LECTURAS
resultados_sensores = leer_sensores()
if resultados_sensores:
    #PUBLICACIÓN DE VALORES EN THINGSPEAK
    grados, longitud = resultados_sensores
    fechaActual = datetime.now()
    fechaActual2 = datetime.strftime(fechaActual, '%d/%m/%Y,%H:%M:%S')
    payload = "field1=" + fechaActual2 + "&field2=" + str(grados) + "&field3="
        + str(longitud)
    publish.single(topic, payload, hostname=mqtt_host, transport=t_transport
        , port=t_port, client_id=mqtt_client_ID, auth={'username': mqtt_username, 
        'password': mqtt_password})
else:
    print("Error al leer sensores. No se publicarán datos MQTT.")
