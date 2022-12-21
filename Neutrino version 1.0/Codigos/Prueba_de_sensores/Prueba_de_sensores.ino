int datos[8];

void setup(){
 Serial.begin(9600); 
  
}

void loop(){
  for(int x=0;x<8;x++){
  datos[x]=analogRead(x);
  
  if(datos[x]>500){
    datos[x]=1;
  }
  else if(datos[x]<=500){
    datos[x]=0;
  } 
  Serial.print(datos[x]);
  Serial.print(" - ");
  delay(20);
     
  }
 Serial.println(); 
  
  
  
}
