# sonar
# Proyecto Final - Sistemas Embebidos

Este repositorio contiene el código y la documentación del proyecto final desarrollado como parte de la asignatura de Sistemas Embebidos. El objetivo principal del proyecto fue implementar un sonar utilizando un servomotor SG90 y un sensor ultrasónico, conectados a una Raspberry Pi 3B+. El sonar mide la distancia en incrementos de 10 grados en un rango de 0 a 180 grados, y luego se devuelve. Adicionalmente, estos valores son enviados a ThingSpeak junto con el timestamp correspondiente, para graficarlos en un sistema de coordenadas polares utilizandon un script de MATLAB. De igual manera, se implementa un servicio en SystemD para reiniciar la rutina de medición, así como asegurar la ejecución periódica del programa diseñado.

## Componentes Utilizados
- Raspberry Pi 3B+
- Servomotor SG90
- Sensor ultrasónico HC-SR04
- ThingSpeak (cuenta y canal configurados)

## Configuración del Hardware

1. Conecta el servomotor SG90 y el sensor ultrasónico a la Raspberry Pi 3B+ según las definiciones de los puertos GPIO hechas en readSensors.c.
2. Asegúrate de tener acceso a Internet para que la Raspberry Pi pueda enviar los datos a ThingSpeak.

## Configuración del Software

Clona este repositorio en la Raspberry Pi:
```bash
git clone https://github.com/JuanFelipeEspana/sonar.git
```

Instala las dependencias necesarias:

```bash
sudo pip3 install paho-mqtt
sudo apt-get install wiringpi
```

## Configura tus credenciales de ThingSpeak en el archivo lectura_python.py:

```python
# lectura_python.py
channel_ID = "XXXXXXX"
mqtt_host ="mqtt3.ThingSpeak.com"
api_key = "XXXXXXXXXXXXXXX"
mqtt_client_ID = "XXXXXXXXXXXXXXXXXXXXXXX"
mqtt_username =  "XXXXXXXXXXXXXXXXXXXXXXX"
mqtt_password = "XXXXXXXXXXXXXXXXXXXXXXX"
```

## Uso
Ejecuta el script principal sonar.sh con permisos de superusuario para iniciar la medición de distancias y la carga de datos a ThingSpeak:

```bash
sudo sonar.sh
```
Este script moverá el servomotor en incrementos de 10 grados, medirá la distancia utilizando el sensor ultrasónico y enviará los datos a ThingSpeak junto con el timestamp correspondiente.

## Visualización de Datos
Para la visualización de datos empleando la plataforma de ThingSpeak, se recomienda diseñar un script de MATLAB que contenga la función polarscatter que recibe como argumentos la distancia y ángulo theta que se desea graficar. Adicionalmente, se sugiere limitar el número de puntos que se desean graficar con el fin de no saturar la visualización.

## YouTube
Aquí puede encontrar un link a un video que demuestra el funcionamiento del proyecto: https://www.youtube.com/watch?v=jD3AdVPmktY

## Contribuciones

Actualmente, la idea es poder trabajar con un sistema que maneje los 360 grados, mejorando el rango de detección. De igual manera, se busca optimizar el código diseñado para hacerlo cumplir estándares que aseguren su funcionamiento.

