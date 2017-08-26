#define LEDPIN 6

  // MKR1000 Pin 6 is built in LED


#define SENSORPIN 7

int sensorState = 0;
int lastState = 0;         

void setup() {
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);     
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  
  Serial.begin(9600);
}

void loop(){
  // read the state of the 7 pin:
  sensorState = digitalRead(SENSORPIN);

  // check if the sensor beam is obstructed
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW); 
  }
  lastState = sensorState;
}
