#include <EEPROMex.h>

long sensors_average;
int sensors_sum;
float position;
float proportional;
float integral;
float derivative;
float last_proportional;
int Set_point=3000;
float right_speed;
float left_speed;
float error_value;
float Kp=0.35;
float Ki=0;
float Kd=5.09;
int max_speed=150;
long sensors[] = {0, 0, 0, 0, 0};
int motor=0;
int valor_bateria;
int accion=-1,linea_izq=0,linea_centro=0,linea_der=0;

void setup(){
//  while(digitalRead(2));
  Serial.begin(115200);
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
  Serial.println(bateria());
  while(digitalRead(2));
}

void sensors_read(){
  sensors_average = 0;
  sensors_sum = 0;
  for (int i = 1; i < 6; i++){
    sensors[i] = analogRead(i);
    sensors_average += sensors[i] * i * 1000;
    sensors_sum += int(sensors[i]);
  }
//  position = int(sensors_average / sensors_sum);
//  Serial.print(position);
}



void pid_calc(){
  position = int(sensors_average / sensors_sum);
  proportional = position-Set_point;
  integral = integral + proportional;
  derivative = proportional - last_proportional;
  last_proportional = proportional;
  error_value = int(proportional * Kp + ((integral * Ki)/100) + derivative * Kd);
 
//  Serial.print(error_value);
//   Serial.print("    ");
}

void calc_turn(){
  if (error_value< -255){
    error_value = -255;
  }
  if (error_value> 255){
    error_value = 255;
  }
  if (error_value < 0){
    right_speed = max_speed ;
    left_speed = max_speed + error_value;
  }else{
    right_speed = max_speed - error_value;
    left_speed = max_speed;
  }
}

void motores(int pwm1, int pwm2){
  int freno=1;
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
   digitalWrite(6,freno);
   digitalWrite(9,freno);

  }
 
  if(pwm2>0){
   digitalWrite(3,LOW);
   analogWrite(5,pwm2);
  }else if(pwm2<0){
   digitalWrite(5,LOW);
   analogWrite(3,-pwm2);
  }else{
   digitalWrite(5,freno);
   digitalWrite(3,freno);
  }
 
  
}

int bateria(){
  valor_bateria=(map(analogRead(7),0,1023,0,500));
  if(valor_bateria<310){
     delay(200);
     if(valor_bateria<310){   
     motores(0,0);
     while(1);
   }
  }
  return valor_bateria;
}

void acciones(){
 
  if(((analogRead(0)<500)&&(analogRead(1)<500))||((analogRead(5)<500)&&(analogRead(6)<500))){
     //Serial.println("                               PRIMERA COMPARACION");
     linea_izq=0;
     linea_der=0;
     linea_centro=0;
     int tiempo=millis();
     while(((analogRead(0)<500)&&(analogRead(1)<500))||((analogRead(5)<500)&&(analogRead(6)<500))){
       if((analogRead(0)<500)&&(analogRead(1)<500)){linea_izq=1;}
       if((analogRead(5)<500)&&(analogRead(6)<500)){linea_der=1;}
          motores(0,0);
     }
     delay(60);
     if(analogRead(3)<500){linea_centro=1;}
     delay(90);
     if((analogRead(0)<500)&&(analogRead(3)<500)&&(analogRead(6)<500)){
     accion=1010; 
     }else {
       accion=linea_izq*100 + linea_centro*10 + linea_der;
     }
  }else if((analogRead(0)>500)&&(analogRead(3)<500)&&(analogRead(6)>500)){
    //Serial.println("                               SEGUNDA COMPARACION AVANZAR");
     accion=10;
     
      
  }else if((analogRead(0)>500)&&(analogRead(1)>500)&&(analogRead(2)>500)&&(analogRead(3)>500)&&(analogRead(4)>500)&&(analogRead(5)>500)&&(analogRead(6)>500)){
     //Serial.println("                               TERCERA COMPARACION 180");
     accion=0; 
  }
  
  
  } 

void giro(int grado){
  switch (grado){
    case 90: 
          motores(180,-180);
          while(analogRead(6)>500){
            motores(180,-180);
          }
          motores(0,0);
          delay(50);
          motores(-100,100);
          while(analogRead(3)>500){
            motores(-100,100);
          }
          motores(0,0);
          delay(50);
          motores(50,-50);
          while(analogRead(3)>500){
            motores(50,-50);
          }
          motores(0,0);
          delay(100);
    break;
    case 270:
          motores(-180,180);
          while(analogRead(0)>500){
            motores(-180,180);
          }
          motores(0,0);
          delay(50);
          motores(100,-100);
          while(analogRead(3)>500){
            motores(100,-100);
          }
          motores(0,0);
          delay(50);
          motores(-50,50);
          while(analogRead(3)>500){
            motores(-50,50);
          }
          motores(0,0);
          delay(100);
    break;
    case 180:
          motores(180,-180);
          while(analogRead(6)>500){
            motores(180,-180);
          }
          motores(0,0);
          delay(50);
          motores(-100,100);
          while(analogRead(3)>500){
            motores(-100,100);
          }
          motores(0,0);
          delay(50);
          motores(50,-50);
          while(analogRead(3)>500){
            motores(50,-50);
          }
          motores(0,0);
          delay(50);
    break;
    
  }
  
}

void mano_derecha(){
    switch (accion){
    case 000:
        //Serial.println("GIRO 180");
        Serial.print("U");
        giro(180);
    break;
    case 10:
        //Serial.println("AVANZAR");
        motores(right_speed, left_speed);
    break;
    case 100:
        //Serial.println("GIRO IZQUIERDA 90");
        giro(270);
    break;
    case 1:
        //Serial.println("GIRO DERECHA 90");
        giro(90);
    break;
    case 101:
        //Serial.println("CRUCE T DESDE CENTRO");
        Serial.print("R");
        giro(90);
        //motores(0, 0);
        //delay(5000);
    break;
    case 110:
        //Serial.println("CRUCE T DESDE DERECHA");
        Serial.print("S");
        //motores(0, 0);
        //delay(5000);
         motores(max_speed, max_speed);
         delay(10);
    break;
    case 11:
        //Serial.println("CRUCE T DESDE IZQUIERDA");
        Serial.print("R");
        giro(90);
        //motores(0, 0);
        //delay(5000);
         //motores(max_speed, max_speed);
         //delay(10);
    break;
    case 111:
        //Serial.println("CRUCE CRUZ");
        Serial.print("R");
        giro(90);
        //motores(0, 0);
        //delay(5000);
         //motores(max_speed, max_speed);
         //delay(10);
    break;
    case 1010:
        Serial.println("FIN LABERINTO");
        motores(0, 0);
        delay(10000);
    break;
    default:
        Serial.println("PUNTO MUERTO");
    break;
    accion=-1;
  }   
   
}

void loop(){
  if(digitalRead(2)==0){
     motores(0,0);
     delay(500);
     while(digitalRead(2));
     delay(500);
  }
 
  bateria();
  sensors_read();
  pid_calc();
  calc_turn();
  acciones();
  mano_derecha();
}




