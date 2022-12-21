#include <EEPROMex.h>
int time=0;
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
float Kp=1.28;
float Ki=0;
float Kd=12.37;
int max_speed=180;
long sensors[] = {0, 0, 0, 0, 0, 0, 0};
int motor=1;
int valor_bateria;

void recibir(){
  if (Serial.available() > 0) {
    int variable=Serial.read();
       switch (variable){
          case 'A':
               Kp=Kp+0.1;
               EEPROM.writeFloat(0,Kp);
               Serial.println(EEPROM.readFloat(0));
          break;
          case 'a':
               Kp=Kp+0.01;
               EEPROM.writeFloat(0,Kp);
               Serial.println(EEPROM.readFloat(0));
          break; 
          case 'B':
               Kp=Kp-0.1;
               EEPROM.writeFloat(0,Kp);
               Serial.println(EEPROM.readFloat(0));
          break;
         case 'b':
               Kp=Kp-0.01;
               EEPROM.writeFloat(0,Kp);
               Serial.println(EEPROM.readFloat(0));
          break;  
          case 'C':
               Ki=Ki+0.1;
               EEPROM.writeFloat(10,Ki);
               Serial.println(EEPROM.readFloat(10));
          break; 
          case 'c':
               Ki=Ki+0.01;
               EEPROM.writeFloat(10,Ki);
               Serial.println(EEPROM.readFloat(10));
          break; 
          case 'D':
               Ki=Ki-0.1;
               EEPROM.writeFloat(10,Ki);
               Serial.println(EEPROM.readFloat(10));
          break;
          case 'd':
               Ki=Ki-0.01;
               EEPROM.writeFloat(10,Ki);
               Serial.println(EEPROM.readFloat(10));
          break; 
          case 'E':
               Kd=Kd+0.1;
               EEPROM.writeFloat(20,Kd);
               Serial.println(EEPROM.readFloat(20));
          break;
          case 'e':
               Kd=Kd+0.01;
               EEPROM.writeFloat(20,Kd);
               Serial.println(EEPROM.readFloat(20));
          break; 
          case 'F':
               Kd=Kd-0.1;
               EEPROM.writeFloat(20,Kd);
               Serial.println(EEPROM.readFloat(20));
          break;
          case 'f':
               Kd=Kd-0.01;
               EEPROM.writeFloat(20,Kd);
               Serial.println(EEPROM.readFloat(20));
          break; 
          case 'G':
               max_speed=max_speed+5;
               if(max_speed>255){max_speed=255;}
               EEPROM.write(30,max_speed);
               Serial.println(EEPROM.read(30));
          break;
         case 'g':
               max_speed=max_speed+1;
               if(max_speed>255){max_speed=255;}
               EEPROM.write(30,max_speed);
               Serial.println(EEPROM.read(30));
          break; 
          case 'H':
               max_speed=max_speed-5;
               if(max_speed<0){max_speed=0;}
               EEPROM.write(30,max_speed);
               Serial.println(EEPROM.read(30));
          break;
         case 'h':
               max_speed=max_speed-1;
               if(max_speed<0){max_speed=0;}
               EEPROM.write(30,max_speed);
               Serial.println(EEPROM.read(30));
          break; 
           case 'M':
               motor=1;
          break; 
           case 'm':
               motor=0;
          break; 
          case 'P':
                Serial.println(EEPROM.readFloat(0));
                Serial.println(EEPROM.readFloat(10));
                Serial.println(EEPROM.readFloat(20));
                Serial.println(EEPROM.read(30));
                
          break; 
          case 'K':
               float floatvalor = valor_bateria;
               floatvalor=floatvalor/100;
               Serial.println(floatvalor);
          break; 

       }
    ////
  }
  
}

void setup(){
//  while(digitalRead(2));
 //Kp=EEPROM.readFloat(0);
 //Ki=EEPROM.readFloat(10);
 //Kd=EEPROM.readFloat(20);
 //max_speed=EEPROM.read(30);

//EEPROM.writeFloat(0,Kp);
//EEPROM.writeFloat(10,Ki);
//EEPROM.writeFloat(20,Kd);
//EEPROM.write(30,max_speed);


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
  while(digitalRead(2));
  delay(3000);
  time=millis();
  
}

void sensors_read(){
  sensors_average = 0;
  sensors_sum = 0;
  for (int i = 0; i < 7; i++){
    sensors[i] = analogRead(i);
    sensors_average += sensors[i] * i * 1000;
    sensors_sum += int(sensors[i]);
  }
 // position = int(sensors_average / sensors_sum);
 // Serial.println(position);
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
}
  
void loop(){
  
  if((millis()-time)<100){
    max_speed=160;
    Kp=0.8;
    Kd=9.37;
    //Serial.println("1");
    
  }else if((millis()-time)>=1000){
    max_speed=255;
  Kp=1.18;
  Kd=14.00;
    //Serial.println("2");
  }
  Serial.println(max_speed);
  bateria();
  //recibir();
  sensors_read();
  pid_calc();
  calc_turn();
  if(motor==1){
    motores(right_speed, left_speed);
  }else if(motor==0){
    motores(0, 0);
  }
  
  if((analogRead(0)>500)&&(analogRead(1)>500)&&(analogRead(2)>500)&&(analogRead(3)>500)&&(analogRead(4)>500)&&(analogRead(5)>500)&&(analogRead(6)>500)){
     //motor=0; 
  }else if((analogRead(0)<500)){
    while(analogRead(3)>500){
     motores(0,255);
    }
  }else if((analogRead(6)<500)){
     while(analogRead(3)>500){
       motores(255,0);
     }
  }
  
  

}
