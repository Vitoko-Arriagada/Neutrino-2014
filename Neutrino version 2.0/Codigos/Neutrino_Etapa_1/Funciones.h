void linea(){
  
  unsigned int position = qtra.readLine(sensorValues);
if(sensorValues[3]<500){
     motores(255,255);
     Serial.println("Adelante");
  }else


if(sensorValues[5]<500){
  motores(200,80);
          Serial.println("derecha lento");
  }else
if(sensorValues[6]<500){
     motores(180,0,1);
     Serial.println("derecha rapido");
  }else

if(sensorValues[1]<500){
     motores(80,200);
      Serial.println("izquierda lento");
  }else
if(sensorValues[0]<500){
     motores(0,180,1);
     Serial.println("izquierda rapido");
  }

   
  
}
  
  
  
