#define adelante 1
#define atras 2
#define alto 3

#define D_1 3
#define D_2 5
#define I_1 6
#define I_2 9

int datos[8];

void setup(){
 Serial.begin(9600); 
 pinMode(D_1, OUTPUT);
 pinMode(D_2, OUTPUT);
 pinMode(I_1, OUTPUT);
 pinMode(I_2, OUTPUT);
  
}


void rueda_derecha(int x){
  switch (x){
   case 1:
      digitalWrite(D_1,LOW);
      digitalWrite(D_2,HIGH);
   break;
     
   case 2:
      digitalWrite(D_1,HIGH);
      digitalWrite(D_2,LOW);
   break;
   
   case 3:
      digitalWrite(D_1,LOW);
      digitalWrite(D_2,LOW);
   break; 
    
  }
  
}


void rueda_izquierda(int x){
  switch (x){
   case 1:
      digitalWrite(I_1,HIGH);
      digitalWrite(I_2,LOW);
   break;
     
   case 2:
      digitalWrite(I_1,LOW);
      digitalWrite(I_2,HIGH);
   break;
   
   case 3:
      digitalWrite(I_1,LOW);
      digitalWrite(I_2,LOW);
   break; 
    
  }
  
}

void leer_sensores(){
    
}


void loop(){
  
}
