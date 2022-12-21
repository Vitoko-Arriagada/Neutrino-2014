int valor;

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
}

void motores(int pwm1, int pwm2){
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
 }else if(pwm1<0){
   digitalWrite(5,LOW);
   analogWrite(3,-pwm2);
 }else{
   digitalWrite(5,LOW);
   analogWrite(3,0);
 }
 
  
}
int pwm1,pwm2;

void loop(){
  
  if (Serial.available() > 0){
     pwm1=Serial.parseInt();
     Serial.println(pwm1);
     while(!Serial.available());
     pwm2=Serial.parseInt();
     Serial.println(pwm2);
     
 
  } 
  motores(pwm1,pwm2);

}
