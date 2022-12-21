int dato;
int numero;
int sensor;
void setup(){
 Serial.begin(9600); 
  
}

void loop(){

  for(int x=0;x<8;x++){
    numero=1;
    for(int y=0;y<x;y++){
       numero=numero*2;
    }
    if(analogRead(x)<500){
      dato=dato+numero;
    }
  }
Serial.print(dato);
Serial.print("--");
  
  switch(dato){
    case 1:sensor=1;break;
    case 3:sensor=2;break;
    case 7:sensor=3;break;
    case 6:sensor=4;break;
    case 14:sensor=5;break;
    case 12:sensor=6;break;
    case 28:sensor=7;break;
    case 24:sensor=8;break;
    case 56:sensor=9;break;
    case 48:sensor=10;break;
    case 112:sensor=11;break;
    case 96:sensor=12;break;
    case 224:sensor=13;break;
    case 192:sensor=14;break;
    case 128:sensor=15;break;
    default:sensor=0;break;
    
  }
  Serial.println(sensor);
  delay(300);
  dato=0;

}
