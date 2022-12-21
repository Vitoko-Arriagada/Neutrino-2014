int POT=100;
void giro_90_derecha(){
      Serial.println("giro 90 derecha");
  motores(255,-255);
  delay(110);
  motores(0,0,1);
}

void giro_90_izquierda(){
     Serial.println("giro 90 izquierda");
   motores(-255,255);
  delay(110);
  motores(0,0,1);
}

void giro_180(){

  Serial.println("giro 180");
   motores(-255,255);
   delay(220);
  
  motores(0,0,1);
  
}

void linea(){
  
  unsigned int position = qtra.readLine(sensorValues);
if(sensorValues[3]<500){
     motores(255-POT,255-POT);
     Serial.println("Adelante");
  }else


if(sensorValues[5]<500){
  motores(200-POT,80);
          Serial.println("derecha lento");
  }else
if(sensorValues[1]<500){
     motores(80,200-POT);
      Serial.println("izquierda lento");
  }


   
  
}
  
  
  
