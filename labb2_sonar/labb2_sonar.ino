#include <NewPing.h>

const int TRIGGER_PIN = 8;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int ECHO_PIN = 9;  // Arduino pin tied to echo pin on the ultrasonic sensor.
const int MAX_DISTANCE = 500; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int LAMP_PIN = 13; // Built in LED pin


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(LAMP_PIN, OUTPUT); // initialize digital pin 13 as an output.
}

void loop() {
  /*
   * Read sensor 
   */
  unsigned int distance = sonar.ping_cm();

  /*
   * Set lamp color
   */
  if(distance < 10){
    digitalWrite(LAMP_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LAMP_PIN, LOW);
  }

  Serial.print(distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println(" cm");
  delay(30);
}


