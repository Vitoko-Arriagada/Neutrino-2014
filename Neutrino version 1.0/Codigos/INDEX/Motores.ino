//motores(int PWM,int PWM);  PWM => -255 a 255
//motores_pines(int a, int b, int c, int d);  a=M1_A - b=M1_B - c=M2_A - d=M2_B
int M1_A,M1_B,M2_A,M2_B;

void motores_pines(int a, int b, int c, int d){
  M1_A=a;
  M1_B=b;
  M2_A=c;
  M2_B=d;
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  
}

void motores(int pwm1, int pwm2){
  if(pwm1>255){pwm1=255;}
  if(pwm1<-255){pwm1=-255;}
  if(pwm2>255){pwm2=255;}
  if(pwm2<-255){pwm2=-255;}
  
  if(pwm1>0){
    digitalWrite(M1_B,LOW);
    analogWrite(M1_A,pwm1);
  }else if(pwm1<0){
    digitalWrite(M1_A,LOW);
    analogWrite(M1_B,-pwm1);
  }else{
    digitalWrite(M1_A,LOW);
    analogWrite(M1_B,0);
  }
 
  if(pwm2>0){
    digitalWrite(M2_B,LOW);
    analogWrite(M2_A,pwm2);
  }else if(pwm2<0){
    digitalWrite(M2_A,LOW);
    analogWrite(M2_B,-pwm2);
  }else{
    digitalWrite(M2_A,LOW);
    analogWrite(M2_B,0);
  }
}
