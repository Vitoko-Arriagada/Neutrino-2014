#define adelante 1
#define atras 2
#define alto 3
#define POWER 50

#define D_1 3
#define D_2 5
#define I_1 6
#define I_2 9
#define BOTON 2

int datos[8];

void setup(){
 Serial.begin(9600); 
 pinMode(D_1, OUTPUT);
 pinMode(D_2, OUTPUT);
 pinMode(I_1, OUTPUT);
 pinMode(I_2, OUTPUT);
 pinMode(BOTON,INPUT);
 digitalWrite(BOTON, HIGH);
 while(digitalRead(BOTON));
}


void rueda_derecha(int x){
  switch (x){
   case 1:
      analogWrite(D_1,0);
      analogWrite(D_2,POWER);
   break;
     
   case 2:
      analogWrite(D_1,POWER);
      analogWrite(D_2,0);
   break;
   
   case 3:
      analogWrite(D_1,0);
      analogWrite(D_2,0);
   break; 
    
  }
  
}


void rueda_izquierda(int x){
  switch (x){
   case 1:
      analogWrite(I_1,POWER);
      analogWrite(I_2,0);
   break;
     
   case 2:
      analogWrite(I_1,0);
      analogWrite(I_2,POWER);
   break;
   
   case 3:
      analogWrite(I_1,0);
      analogWrite(I_2,0);
   break; 
    
  }
  
}

void leer_sensores(){
    for(int x=0;x<8;x++){
       datos[7-x]=analogRead(x); 
       if(datos[7-x]>630){
         datos[7-x]=1;
       }else if(datos[7-x]<=630){
         datos[7-x]=0;
       }
    }
    
}

void avanza(){
  rueda_izquierda(adelante);
  rueda_derecha(adelante);
}

void gira_derecha(){
  rueda_izquierda(adelante);
  rueda_derecha(alto);
}

void gira_izquierda(){
  rueda_izquierda(alto);
  rueda_derecha(adelante);
}

void gira_derecha_90(){
  rueda_izquierda(adelante);
  rueda_derecha(atras);
}

void gira_izquierda_90(){
  rueda_izquierda(atras);
  rueda_derecha(adelante);
}

void loop(){
  leer_sensores();
  if((datos[0]==1)&&(datos[1]==1)&&(datos[2]==1)&&(datos[3]==0)&&(datos[4]==0)&&(datos[5]==1)&&(datos[6]==1)&&(datos[7]==1)){
     avanza();
  }
  else
  if((datos[0]==1)&&(datos[1]==0)&&(datos[2]==0)&&(datos[3]==0)&&(datos[4]==1)&&(datos[5]==1)&&(datos[6]==1)&&(datos[7]==1)){
     gira_izquierda();
  }
  else
  if((datos[0]==1)&&(datos[1]==1)&&(datos[2]==1)&&(datos[3]==0)&&(datos[4]==0)&&(datos[5]==0)&&(datos[6]==1)&&(datos[7]==1)){
     gira_derecha();
  }
 

}
