#include <Arduino.h>
#include <EEPROM.h>
#include "funciones.h"

void imprimir(){
   for(int x=0; x<8;x++){
     Serial.print(maximo[x]);
     Serial.print("   "); 
   }
   Serial.println("");
   for(int x=0; x<8;x++){
     Serial.print(minimo[x]);
     Serial.print("   "); 
   }
   Serial.println("");

    for(int x=0; x<8;x++){
     Serial.print(EEPROM.read(10+x)*4);
     Serial.print("   "); 
   }
   Serial.println("");
   for(int x=0; x<8;x++){
     Serial.print(EEPROM.read(20+x)*4);
     Serial.print("   "); 
   }
   Serial.println("");
 
}
void setup(){
  Serial.begin(9600);
   Serial.setTimeout(50);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(2,INPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  while(digitalRead(2));
 // Serial.println("Calibracion en proceso...");
 // calibracion();
 // Serial.println("Calibracion Listo!!");
  while(digitalRead(2));
//  imprimir();
}

void loop(){
leer_sensor();
}



