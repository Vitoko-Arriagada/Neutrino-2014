
int last_proportional;
int proportional;
int derivative;
const int max = 255;
int power_difference;
int integral;

void sigue_lineas(){
unsigned int position = qtra.readLine(sensorValues);

// The "proportional" term should be 0 when we are on the line.
proportional = ((int)position) - 3500;
 Serial.println((int)position);
// Compute the derivative (change) and integral (sum) of the
// position.

derivative = proportional - last_proportional;
integral += proportional;
 
// Remember the last position.
last_proportional = proportional;

power_difference = proportional*(2) + integral*(0.135) + derivative*(6.6);
 
// Compute the actual motor settings.  We never set either motor
// to a negative value.

if(power_difference > max)
    power_difference = max;
if(power_difference < -max)
    power_difference = -max;
 
if(power_difference < 0)
    motores(max+power_difference, max,0);
else
    motores(max, max-power_difference,0);
/*
if(analogRead(0)<500){
    motores(100, -100);
 
}
if(analogRead(7)<500){
    motores(-100,100);
  }
*/
}
