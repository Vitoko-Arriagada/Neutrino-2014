void condicion(byte decimal){
//  Serial.println(decimal);
  switch (decimal){
     case B11100111: motores(power*3,power*3);Serial.println("Derecho");break;
     case B11001111: motores(power/5,power);Serial.println("Gira Izquierda Leve");break;
     case B10011111: motores(0,power);Serial.println("Gira Izquierda Fuerte");break;
     case B00111111: motores(-(power/2),power);Serial.println("Gira Izquierda FULL");break;
     case B11110011: motores(power,power/5);Serial.println("Gira Derecha Leve");break;
     case B11111001: motores(power,0);Serial.println("Gira Derecha Fuerte");break;
     case B11111100: motores(power,-(power/2));Serial.println("Gira Derecha FULL");break;
     case B11111111: ;Serial.println("STOP");break;
     case B00001111: motores(-power,power);Serial.println("giro 90 izquierda");break;
     case B00000111: motores(-power,power);Serial.println("giro 90 izquierda");break;
     case B00000011: motores(-power,power);Serial.println("giro 90 izquierda");break;
     case B11000000: motores(power,-power);Serial.println("giro 90 derecha");break;
     case B11100000: motores(power,-power);Serial.println("giro 90 derecha");break;
     case B11110000: motores(power,-power);Serial.println("giro 90 derecha");break;
     
    }
}
