/*
  Motion Sensor - 6 input, 5 led
  Toggle Button - 7 input, 4 led
  Push Button - 8 input, 3 led
  Breaker Beam - input 9, 2 led

  Inputs turn on/off their respective LEDs

*/

const int mSensor = 6;     // the number of the pushbutton pin
const int mSensorLED =  5;      // the number of the LED pin
const int tButton = 7;     // the number of the pushbutton pin
const int tButtonLED =  4;      // the number of the LED pin
const int pButton = 8;     // the number of the pushbutton pin
const int pButtonLED =  3;      // the number of the LED pin
const int bBeam = 9;     // the number of the pushbutton pin
const int bBeamLED =  2;      // the number of the LED pin

// variables will change:
int mSensorState = 0; // Status for PIN 6
int mSensorStatus = 0;    // State of motion

int tButtonState = 0;  // Status for PIN 7

int pButtonState = 0;  // Status for PIN 8  

int bBeamState = 0;  // Status for PIN 9

void setup() {
  // set the LED pins as an output:
  pinMode(mSensorLED, OUTPUT);
  pinMode(tButtonLED, OUTPUT);
  pinMode(pButtonLED, OUTPUT);
  pinMode(bBeamLED, OUTPUT);
  
  // set the sensor pins as an input:
  pinMode(mSensor, INPUT);
  pinMode(tButton, INPUT);
  pinMode(pButton, INPUT);
  pinMode(bBeam, INPUT);

  digitalWrite(bBeam, HIGH); // turn on the pullup

Serial.begin(9600);
  
}

void loop() {
  
  mSensorState = digitalRead(mSensor);
  tButtonState = digitalRead(tButton);
  pButtonState = digitalRead(pButton);
  bBeamState = digitalRead(bBeam);


// check Motion Sensor:
 mSensorState = digitalRead(mSensor);  // read pin 6
  if (mSensorState == HIGH) {            // if pin 6 is HIGH
    digitalWrite(mSensorLED, HIGH);  // turn LED ON
    if (mSensorStatus == 0) {

      Serial.println("Motion detected!"); //mSensorStatus allows us to only print motion once. 

      mSensorStatus = 1;
    }
  } else {
    digitalWrite(mSensorLED, LOW); // turn LED OFF
    if (mSensorStatus == 1){
      
      Serial.println("Motion ended!");
      
      mSensorStatus = 0;
    }
  }
  
  
  // check Toggle Button:
  if (tButtonState == HIGH) {
    // turn LED on:
    digitalWrite(tButtonLED, HIGH);
  } else {
    // turn LED off:
    digitalWrite(tButtonLED, LOW);
  }


  // check Push Button:
if (pButtonState == HIGH) {
    // turn LED on:
    digitalWrite(pButtonLED, HIGH);
  } else {
    // turn LED off:
    digitalWrite(pButtonLED, LOW);
  }


// check Breaker Beam:
if (bBeamState == HIGH) {     
    // turn LED on:
    digitalWrite(bBeamLED, LOW);  
  } 
  else {
    // turn LED on:
    digitalWrite(bBeamLED, HIGH); 
  }
  
}
