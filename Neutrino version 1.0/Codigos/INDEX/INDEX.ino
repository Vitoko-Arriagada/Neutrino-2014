int power=60;
int x=0;
void setup(){
 motores_pines(6,9,5,3);
 pinMode(2,INPUT);
 digitalWrite(2,HIGH);
 while(digitalRead(2));
 Serial.begin(9600);
}
void loop(){
//  Serial.println(leer_sensores());
  condicion(leer_sensores());
}
