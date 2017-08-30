/*
IoT Showcase - Zachary Daulton

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
// constants
const int servoPin = 3;
const int feedbackPin = A0;
const int p1Button = 5;     // the number of the left pushbutton pin
const int p1ButtonLED =  4;      // the number of its LED pin
const int p2Button = 0;     // the number of the right pushbutton pin
const int p2ButtonLED =  2;      // the number of its LED pin
const int tButton = 6;     // the number of the toggle button pin
const int tButtonLED =  7;      // the number of its LED pin

String servofeedback;
const int numReadings = 5;

int readings[numReadings];      // the readings from the potentiometer input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// changing variables:
int p1ButtonState = 0;  // Status for PIN 5  
int p1sent1 = false; // state for p1 communications
int p1sent0 = false; // state for p1 communications
int p2sent1 = false; // state for p2 communications
int p2sent0 = false; // state for p2 communications
int p2ButtonState = 0;  // Status for PIN 2 
int tButtonState = 0;  // Status for PIN 6


void setup() {
Serial.begin(9600);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }                 // logging the potentiometer data for software smoothin - also being smoothed through a low-pass filter in the circuit
  
  Serial.begin(9600);
  WiFi.begin(ssid, pass);             // seeks out ip and sends connection info
  
                   // set the LED pins as an output:
  pinMode(tButtonLED, OUTPUT);
  pinMode(p1ButtonLED, OUTPUT);
  pinMode(p2ButtonLED, OUTPUT);
  
                  // set the sensor pins as an input:
  pinMode(tButton, INPUT);
  pinMode(p1Button, INPUT);
  pinMode(p2Button, INPUT);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly. IP set from using personal mobile router
  client.begin("192.168.0.100", net);
  client.onMessage(messageReceived);

  connect();

  
}

// begin runtime

void loop() {
client.loop();

  if (!client.connected()) {           // if the client is not connected, hangs until it connects
    connect();
  }

                                              // read and save the input states
  tButtonState = digitalRead(tButton);
  p1ButtonState = digitalRead(p1Button);
  p2ButtonState = digitalRead(p2Button);
  servofeedback = analogRead(feedbackPin);

                                                // If toggle button is closed, set state to HIGH and run servofeedback logging. Send data to /servo
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
                                // send it to the computer as a string
  Serial.println(String(average));
  delay(1);                           // delay in between reads for stability 
    client.publish("/servo", String(average));
    delay(50);                          // delay total read to prevent going over message buffer
}
else {
            // turn LED off:
    digitalWrite(tButtonLED, LOW);
    myservo.detach();                   // Detaches servo allowing the user to manipulate it
     } 


                                             // check left Push Button, if closed, set state to HIGH and send a single message indicating state
if (p1ButtonState == HIGH) {
           
    digitalWrite(p1ButtonLED, HIGH);

    if (p1sent1 == false){  
   client.publish("/p1", String(1));
   p1sent1 = true;
   p1sent0 = false;
  }
   
  } else {                                  // if circuit is open, check if previous state was closed, if so, send 0 to indicate the connection is now closed
    // turn LED off:
    digitalWrite(p1ButtonLED, LOW);

if (p1sent0 == false){

    client.publish("/p1", String(0));
    p1sent1 = false;
    p1sent0 = true;
     } 

  }
                                         // repeat logic from left button to right button
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


                                                  // Connect function. Prints its current steps. 
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");                        // IP is found, prints its attempts to connect
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");                                   // Subscribes to the /hello channel and sends a test message
  // client.unsubscribe("/hello");
  client.publish("/hello", "1");
}

void messageReceived(String &topic, String &payload) {                // Prints all messages received on the subscribed channels
  Serial.println("incoming: " + topic + " - " + payload);
}
