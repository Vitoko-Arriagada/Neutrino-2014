int datos[8];
int valor=0;
byte leer_sensores(){
    valor=0;
    for(int x=0;x<8;x++){
      datos[7-x]=analogRead(7-x); 
       if(datos[7-x]>500){
         datos[7-x]=1;
         valor=valor + 1;
        }else{
         datos[7-x]=0;
         valor=valor + 0;
       }
     if(x<7){
     valor=valor<<1;
     }
    }
    return valor;
}
