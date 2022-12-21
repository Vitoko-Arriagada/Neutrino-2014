#include <Arduino.h>
#include <QTRSensors.h>
#include "Inicio.h"
#include "Motores.h"
#include "Calibracion.h"
#include "Sigue_lineas.h"
#include "Test_bateria.h"
#include "Funciones.h"


void setup(){

 iniciar(); 
 while(digitalRead(2));
 calibrar();
 while(digitalRead(2)); 
}

void loop(){
 linea();
 
 if((sensorValues[0]<500)){
     giro_90_izquierda();
  }else 
 if((sensorValues[6]<500)){
     giro_90_derecha();
  }else 
if((sensorValues[3]>500)&&(sensorValues[1]>500)&&(sensorValues[5]>500)){
     giro_180();
  }
  
}

