
void motores(int pwm1, int pwm2, int freno){  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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
   digitalWrite(6,0);
   digitalWrite(9,0);

 }
 
 if(pwm2>0){
   digitalWrite(3,LOW);
   analogWrite(5,pwm2);
 }else if(pwm2<0){
   digitalWrite(5,LOW);
   analogWrite(3,-pwm2);
 }else{
   digitalWrite(5,0);
   digitalWrite(3,0);
 }
 
  
}
