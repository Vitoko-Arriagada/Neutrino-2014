#include <Arduino.h>
#include <EEPROMex.h>
int n;

int valor_bateria;
long sensors_average;
int sensors_sum;
long sensors[] = {0, 0, 0, 0, 0, 0, 0};
float position;
float proportional;
float integral;
float derivative;
float last_proportional;
int Set_point=3000;
float error_value;
float Kp=0.40;
float Ki=0;
float Kd=4.30;
float right_speed;
float left_speed;
//unsigned char dir;
unsigned char path[300];
unsigned int path_length=0;
int dato[300];
int dato2[300];

int max_speed=200; //90 es perfect
int vel_giro=150;

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
  delay(1000);
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

void turn(int dir){
	switch(dir){
		case 'L':	// Turn left.
                        Serial.print("L");
			motores(-vel_giro,vel_giro);
                        while(analogRead(0)>500){
                            motores(-vel_giro,vel_giro);
                        }
                        motores(vel_giro,-vel_giro);
                        delay(50);
                        while(analogRead(3)>500){
                            motores(vel_giro,-vel_giro);
                        }
                        motores(-vel_giro,vel_giro);
                        delay(50);
                        motores(vel_giro,-vel_giro);
                        delay(50);
                        /*while(analogRead(3)>500){
                            motores(-30,30);
                        }*/
                        motores(0,0);
                        
		break;
		case 'R':	// Turn right.
                        Serial.print("R");
			motores(vel_giro,-vel_giro);
                        while(analogRead(6)>500){
                            motores(vel_giro,-vel_giro);
                        }
                        motores(-vel_giro,vel_giro);
                        delay(50);
                        while(analogRead(3)>500){
                            motores(-vel_giro,vel_giro);
                        }
                        motores(vel_giro,-vel_giro);
                        delay(50);
                        motores(-vel_giro,vel_giro);
                        delay(50);
                        /*
                        while(analogRead(3)>500){
                            motores(30,-30);
                        }
                        */
                        motores(0,0);
		break;
		case 'U':	// Turn around.
                         Serial.print("U");
                        motores(vel_giro,-vel_giro);
                        while(analogRead(6)>500){
                            motores(vel_giro,-vel_giro);
                        }
                        motores(-vel_giro,vel_giro);
                        delay(50);
                        motores(-vel_giro,vel_giro);
                        while(analogRead(3)>500){
                            motores(-vel_giro,vel_giro);
                        }
                        motores(vel_giro,-vel_giro);
                        delay(50);
                        motores(vel_giro,-vel_giro);
                        while(analogRead(3)>500){
                            motores(vel_giro,-vel_giro);
                        }
                        motores(0,0);
                        
                        
                        
		break;
		case 'S':	// Don’t do anything!
			 //Serial.print("S");
		      
		break;
	}
}



int select_turn( int found_left,int found_straight, int found_right){
	if(found_left)return 'L';
	else if(found_straight)return 'S';
	else if(found_right)return 'R';
	else return 'U';
}

void leer_sensores(){
	sensors_average = 0;
	sensors_sum = 0;
	for (int i = 0; i < 7; i++){
		sensors[i] = analogRead(i);
		sensors_average += sensors[i] * i * 1000;
		sensors_sum += int(sensors[i]);
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


void sigue_lineas(){
	while(1){
		leer_sensores();
		position = int(sensors_average / sensors_sum);
		proportional = position-Set_point;
		integral = integral + proportional;
		derivative = proportional - last_proportional;
		last_proportional = proportional;
		error_value = int(proportional * Kp + ((integral * Ki)/100) + derivative * Kd);
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
		motores(right_speed, left_speed);
                if(sensors[1] > 500 && sensors[3] > 500 && sensors[5] > 500){
			return;
		}
		if(sensors[0] < 500 || sensors[6] < 500){
			return;
		}

                
	}
}

void loop(){
      while(0){
        if ( Serial.available()) // Check to see if at least one character is available
        {int k=Serial.read();
             switch (k){
               case 'A':
                   Kp=Kp + 0.1;
               break;
               case 'a':
                   Kp=Kp + 0.01;
               break;
               case 'B':
                   Kp=Kp - 0.01;
               break;
               case 'b':
                   Kp=Kp - 0.1;
               break;
               case 'C':
                   Kd=Kd + 0.01;
               break;
               case 'c':
                   Kd=Kd + 0.1;
               break;
               case 'D':
                   Kd=Kd - 0.01;
               break;
               case 'd':
                   Kd=Kd - 0.1;
               break;
               case 'R':
                   break;
               break;
               
               
             }
             Serial.print("Kp= ");
             Serial.println(Kp);
             Serial.print("Kd= ");
             Serial.println(Kd);
             
        }
        
        sigue_lineas();
         
      }
      //Serial.println("PRIMER LOOP");
     /* while(analogRead(6)>500){
        motores(70,70);
      }
      while(analogRead(6)<500){
         motores(90,90);
      }
      motores(0,0);
      //delay(1000);
      */
      
      while(1){
		sigue_lineas();
		motores(50,50);
		delay(10);
		int found_left=0;
		int found_straight=0;
		int found_right=0;
		leer_sensores();
		if(sensors[0] < 500){found_left=1;}
		if(sensors[6] < 500){found_right=1;}
		motores(40,40);
		delay(35);
		leer_sensores();
		if(sensors[2] < 500 || sensors[3] < 500 || sensors[4] < 500){found_straight = 1;}
		if(sensors[0] < 350 && sensors[2] < 350 && sensors[6] < 350){break;}
		int dir = select_turn(found_left, found_straight, found_right);
		turn(dir);
		path[path_length] = dir;
		path_length ++;
		//simplify_path();

	}
        motores(0,0);
        Serial.println("FIN DEL PRIMER LOOP");
        Serial.println("FIN DEL PRIMER LOOP");
        int x=0;
        
        for(x=0;x<path_length;x++){
          // Serial.print(" ");
          // Serial.write(path[x]);
         //  delay(50); 
        }
        //Serial.println();
        //Serial.println(x);
        //Serial.println(path_length);
        
        for(int r=0;r<300;r++){
          dato[r]=path[r]; 
          
        }
        
        
   int L=1;
while(L){
	n=2;
	L=0;
	while(1){
		if((dato[n-1]=='U')){
			if((dato[n-2]=='L')&&(dato[n]=='L')){dato[n-2]='S';}
			else if((dato[n-2]=='L')&&(dato[n]=='R')){dato[n-2]='U';}
			else if((dato[n-2]=='L')&&(dato[n]=='S')){dato[n-2]='R';}
			else if((dato[n-2]=='R')&&(dato[n]=='L')){dato[n-2]='U';}
			else if((dato[n-2]=='R')&&(dato[n]=='R')){dato[n-2]='S';}
			else if((dato[n-2]=='R')&&(dato[n]=='S')){dato[n-2]='L';}
			else if((dato[n-2]=='S')&&(dato[n]=='L')){dato[n-2]='R';}
			else if((dato[n-2]=='S')&&(dato[n]=='R')){dato[n-2]='L';}
			else if((dato[n-2]=='S')&&(dato[n]=='S')){dato[n-2]='U';} 
		for(int m=n;m<=path_length;m++){
			dato[m-1]=dato[m+1]; 
		}
		path_length=path_length-2;
		L=1;
		break;
		}
	n++;
	if(n>path_length)break;
	}
}
 
for(int x=0;x<=path_length;x++){
//  Serial.write(dato[x]);
//  Serial.print(" "); 
 }
 
//  Serial.println();
  
 for(int x=0;x<=path_length;x++){
   if(dato[x]=='L'){
     dato2[path_length-(x+1)]='R';
  }else if(dato[x]=='R'){
     dato2[path_length-(x+1)]='L';
  }else{
    dato2[path_length-(x+1)]=dato[x];
  }
 }
 
 
for(int x=0;x<path_length;x++){
//  Serial.write(dato2[x]);
//  Serial.print(" "); 
 }
// Serial.println();
 
/* while(analogRead(6)<500){
     motores(vel_giro,-vel_giro);
 }*/
 //turn('U');
        
        while(digitalRead(2));
        //delay(1000);
        //Serial.println("SEGUNDO LOOP");
        while(1){
        int i;
        for(i=0;i<=path_length;i++){
          sigue_lineas();
          while((analogRead(0)<500)||(analogRead(6)<500)){
             motores(90,90); 
          }
          motores(0,0);
          turn(dato2[i]);
          //delay(1000);
          
        }
        //sigue_lineas();
        break;
        }
        while(analogRead(6)<500){
        motores(70,70);
      }
   
      
      sigue_lineas();
      motores(0,0);
       
       // Serial.print("FIN SEGUNDO LOOP");
        while(1);
}




