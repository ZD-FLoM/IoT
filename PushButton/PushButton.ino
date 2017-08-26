/*
  Button

  Turns on and off digital pin 6, when pressing a pushbutton attached to pin 8.

  The circuit:
  - LED attached from pin 6 - built into board
  - pushbutton attached to pin 8 from +5V
  - 15K resistor attached to pin 2 from ground
*/

const int buttonPin = 8;     // the number of the pushbutton pin
const int ledPin =  6;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // set the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // set the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of pin 8:
  buttonState = digitalRead(buttonPin);

  // check if pin 8 is recieving a signal. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
