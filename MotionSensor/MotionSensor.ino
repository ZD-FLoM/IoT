/*
 * PIR sensor
 */
 
int ledPin = 6;                //LED
int inputPin = 8;               // input pin
int pirState = LOW;             // no motion
int val = 0;                    // pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // LED as output
  pinMode(inputPin, INPUT);     // sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read pin 8
  if (val == HIGH) {            // if pin 8t is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {

      Serial.println("Motion detected!");
      // Only want to print on the output change
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      
      Serial.println("Motion ended!");
      
      pirState = LOW;
    }
  }
}
