/*

  Toggle Button x 1
  Push Button x 2
  Servo - feedback POT, minpos 120, maxpos 699 x 1

  Inputs turn on/off their respective LEDs

*/

#include <Servo.h> 
#include <WiFi101.h>   // Libraries to include for code
#include <MQTTClient.h>

const char ssid[] = "Projection";
const char pass[] = "artisfun";

unsigned long lastMillis = 0;

Servo myservo;  //pointing to 'myservo' as a Servo
WiFiClient net;
MQTTClient client;

const int servoPin = 3;
const int feedbackPin = A0;
const int p1Button = 5;     // the number of the pushbutton pin/////
const int p1ButtonLED =  4;      // the number of the LED pin/////
const int p2Button = 0;     // the number of the pushbutton pin
const int p2ButtonLED =  2;      // the number of the LED pin
const int tButton = 6;     // the number of the pushbutton pin
const int tButtonLED =  7;      // the number of the LED pin

String servofeedback;
const int numReadings = 5;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// variables will change:
int p1ButtonState = 0;  // Status for PIN 8  
int p1sent1 = false;
int p1sent0 = false;
int p2sent1 = false;
int p2sent0 = false;
int p2ButtonState = 0;  // Status for PIN 10 
int tButtonState = 0;  // Status for PIN 7


void setup() {
Serial.begin(9600);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  // set the LED pins as an output:

  pinMode(tButtonLED, OUTPUT);
  pinMode(p1ButtonLED, OUTPUT);
  pinMode(p2ButtonLED, OUTPUT);
  
  // set the sensor pins as an input:

  pinMode(tButton, INPUT);
  pinMode(p1Button, INPUT);
  pinMode(p2Button, INPUT);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("192.168.0.100", net);
  client.onMessage(messageReceived);

  connect();




}

void loop() {
client.loop();

  if (!client.connected()) {
    connect();
  }


 tButtonState = digitalRead(tButton);
  p1ButtonState = digitalRead(p1Button);
  p2ButtonState = digitalRead(p2Button);
  servofeedback = analogRead(feedbackPin);


if (tButtonState == HIGH) {
digitalWrite(tButtonLED, HIGH);
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(feedbackPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(String(average));
  delay(1);        // delay in between reads for stability 
    client.publish("/servo", String(average));
    delay(50);
}
else {
    // turn LED off:
    digitalWrite(tButtonLED, LOW);
    myservo.detach();
     } 


  // check Push Button:
if (p1ButtonState == HIGH) {
    // turn LED on:
    digitalWrite(p1ButtonLED, HIGH);

    if (p1sent1 == false){  
   client.publish("/p1", String(1));
   p1sent1 = true;
   p1sent0 = false;
  }
   
  } else {
    // turn LED off:
    digitalWrite(p1ButtonLED, LOW);

if (p1sent0 == false){

    client.publish("/p1", String(0));
    p1sent1 = false;
    p1sent0 = true;
     } 

  }
       // check Push Button:
if (p2ButtonState == HIGH) {
    // turn LED on:
    digitalWrite(p2ButtonLED, HIGH);

  if (p2sent1 == false){  
   client.publish("/p2", String(1));
   p2sent1 = true;
   p2sent0 = false;
  }
  
  } else {
    // turn LED off:
    digitalWrite(p2ButtonLED, LOW);
    

if (p2sent0 == false){

    client.publish("/p2", String(0));
    p2sent1 = false;
    p2sent0 = true;
    } 
}
}
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
  client.publish("/hello", "1");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}
