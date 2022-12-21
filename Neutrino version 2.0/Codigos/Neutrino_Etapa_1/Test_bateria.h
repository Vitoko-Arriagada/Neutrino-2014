
int bateria(){
  int valor=(map(analogRead(7),0,1023,0,500));
  if(valor<385){
     delay(200);
     if(valor<310){   
     Serial.print(valor);
     Serial.println("  Bateria baja!!!");
     motores(0,0,1);
     while(1){
      Serial.print(bateria());
      Serial.println("  Bateria baja!!!");
      delay(500);
     } 
  }
  }
  return valor;
}
