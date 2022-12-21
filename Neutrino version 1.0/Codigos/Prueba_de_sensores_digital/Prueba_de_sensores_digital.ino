int datos[8];

void setup(){
 Serial.begin(9600); 
  
}

void loop(){
  for(int x=0;x<8;x++){
  datos[7-x]=analogRead(x);
  
  if(datos[7-x]>500){
    datos[7-x]=1;
  }
  else if(datos[7-x]<=500){
    datos[7-x]=0;
  } 
  Serial.print(datos[x]);
  Serial.print(" - ");
  delay(20);
     
  }
 Serial.println(); 
  
  
  
}
