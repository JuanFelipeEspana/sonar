//LIBRERÍAS
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//DEFINICIONES
#define SERVO_PIN 18  // Pin GPIO para el control del servomotor
#define TRIG_PIN 23 // Pin GPIO para el trigger del sensor ultrasónico
#define ECHO_PIN 24 // Pin GPIO para el echo del sensor ultrasónico

//PROTOTIPOS
void setup();
void moveServo(int angle);
void cleanup();
double getDistance();

int main(int argc, char* argv[]){
  //SE RECIBE POR CONSOLA EL ÁNGULO A MOVER EL SERVOMOTOR
  int angle = atoi(argv[1]);
  double distance = 0;
  double rawDistance = 0;
  FILE *log;
  //CONFIGURAMOS LOS PINES DE LA RASPBERRY PI
  setup();
  //CREAMOS EL ARCHIVO
  log = fopen("data.txt", "w");
  delay(50);
  //MOVEMOS EL SERVO AL ANGULO OBJETIVO
  moveServo(angle);
  delay(50);
  //REALIZAMOS LA MEDICION DE DISTANCIA
  rawDistance = getDistance();
  //SE VERIFICA QUE NO SUPERE LOS 10cm
  distance = (rawDistance > 10) ? 10 : rawDistance;
  //SE ESCRIBE EN EL ARCHIVO
  fprintf(log,"%d,%.2f\n", angle, distance);
  printf("ANGLE:%d,DISTANCE:%.2f\n", angle, distance);
  //SE CIERRA EL ARCHIVO
  fclose(log);
  //SE LIMPIA LA CONFIGURACIÓN DEL PIN PWM
  cleanup();
}

void setup() {
    //SE UTILIZA LA CONFIGURACIÓN GPIO DE LOS PINES
    wiringPiSetupGpio();
    pinMode(SERVO_PIN, PWM_OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    //SE CONFIGURA EL PWM
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(192);
    pwmSetRange(2000);
    
    digitalWrite(TRIG_PIN, LOW);
}

void moveServo(int angle) {
    //SE DEFINE EL ANCHO DE PULSO A PARTIR DE LA CARACTERIZACIÓN
    int pulseWidth = 36 + (angle * 200) / 180;
    //SE MUEVE EL SERVO
    pwmWrite(SERVO_PIN, pulseWidth);
    delay(1000);
}

void cleanup(){
  pwmWrite(SERVO_PIN, 0);
}

double getDistance() {
    //SE PRODUCE UN PULSO DE TRIGGER PARA EMPEZAR LA
    //MEDICIÓN
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    //ESPERA A QUE REGRESE EL ECHO
    while (digitalRead(ECHO_PIN) == LOW);
    //MIDE EL TIEMPO QUE SE MANTIENE EN ALTO ECHO
    long startTime = micros();
    //ESPERA A QUE TERMINE DE SENSAR LA DISTANCIA
    while (digitalRead(ECHO_PIN) == HIGH);

    //GUARDA EL TIEMPO EN ALTO
    long endTime = micros();
    //SE CALCULA LA DISTANCIA EN CM
    double distance = (double)(endTime - startTime)/ 70.0;

    return distance;
}