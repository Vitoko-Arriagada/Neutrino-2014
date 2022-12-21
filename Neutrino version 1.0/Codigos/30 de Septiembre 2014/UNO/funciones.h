int valsensor[8];
int maximo[8]={0,0,0,0,0,0,0,0};
int minimo[8]={1023,1023,1023,1023,1023,1023,1023,1023};
int valor,numero,sensor,lado;
unsigned long dato;
int potencia = 100;

int error, P, I, D, error_antiguo,PID_valor;
int Kp = 1/20;
int Ki = 1/10000;
int Kd = 3/2;


void motores(int pwm1, int pwm2){  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 if(pwm1>255){pwm1=255;}
  if(pwm1<-255){pwm1=-255;}
  if(pwm2>255){pwm2=255;}
  if(pwm2<-255){pwm2=-255;}
  
  if(pwm1>0){
   digitalWrite(9,LOW);
   analogWrite(6,pwm1);
 }else if(pwm1<0){
   digitalWrite(6,LOW);
   analogWrite(9,-pwm1);
 }else{
   digitalWrite(6,LOW);
   analogWrite(9,0);

 }
 
 if(pwm2>0){
   digitalWrite(3,LOW);
   analogWrite(5,pwm2);
 }else if(pwm2<0){
   digitalWrite(5,LOW);
   analogWrite(3,-pwm2);
 }else{
   digitalWrite(5,LOW);
   analogWrite(3,0);
 }
 
  
}

void calibracion(){   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   
   for(int y=0; y<170; y++){
     
     if(y <50){
       motores(-35,35);
     }else if(y<130){
       motores(35,-35);
     }else if(y<170){
       motores(-35,35);
     }
     
     for(int x=0; x<8; x++){
       delay(1);
        valor = analogRead(7-x);
        if (valor > maximo[x]) {
           maximo[x] = valor;
        }
        if (valor < minimo[x]) {
           minimo[x] = valor;
        }
     }
   }
    motores(0,0);
/*
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
  */ 
  
}

void sigue_linea(int posicion){
 error = posicion - 2500;
// Serial.print("Error= ");
// Serial.println(error);
 P = error;
 P = map(P,-2500,2500,-1000,1000);
// Serial.print("P= ");
// Serial.println(P);
 I = (I + error) * Ki;
// Serial.print("I= ");
// Serial.println(I);
 D = (error - error_antiguo);
 D = map(D,-2500,2500,-10,10);
// Serial.print("D= ");
// Serial.println(D);
 error_antiguo = error;
// Serial.print("Error Antiguo= ");
// Serial.println(error_antiguo);
 PID_valor= (P) + (I) + (D);
// Serial.print("Valor PID= ");
 Serial.println(PID_valor);
 if(PID_valor>potencia){
    PID_valor=potencia;
 }
 if(PID_valor<-potencia){
    PID_valor=-potencia;
 } 
// Serial.print("Valor PID despues= ");
// Serial.println(PID_valor);
 
 if(PID_valor<0){
   motores(potencia,potencia+PID_valor); 
 }else{
   motores(potencia-PID_valor,potencia);
 }
 //  delay(1000);
}

int leer_sensor(){     //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 unsigned long dato1=((1023-analogRead(0))*0);
 unsigned long dato2=((((1023-analogRead(1))+(1023-analogRead(2)))/2)*1000);
 unsigned long dato3=((((1023-analogRead(3))+(1023-analogRead(4)))/2)*2000);
 unsigned long dato4=((((1023-analogRead(5))+(1023-analogRead(6)))/2)*3000);
 unsigned long dato5=((1023-analogRead(0))*4000);
 unsigned long denominador=((1023-analogRead(0))+(1023-analogRead(1))+(1023-analogRead(2))+(1023-analogRead(3))+(1023-analogRead(4))+(1023-analogRead(5))+(1023-analogRead(6))+(1023-analogRead(7)));
  dato=(dato1+dato2+dato3+dato4+dato5)/denominador;
  Serial.println(dato);
  
}
