
#define NUM_SENSORS             7
#define NUM_SAMPLES_PER_SENSOR  4
#define EMITTER_PIN             12

QTRSensorsAnalog qtra((unsigned char[]) {3, 2, 1, 0, 4, 5, 6}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

int iniciar(){
  Serial.begin(9600);
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
}


