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
 while(digitalRead(2)){
   Serial.println(bateria());
 } 
}

void loop(){
linea();

  
}

