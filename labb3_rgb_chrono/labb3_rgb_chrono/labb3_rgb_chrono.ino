#include <Chrono.h>
#include <NewPing.h>

const int TRIGGER_PIN = 8;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int ECHO_PIN = 9;  // Arduino pin tied to echo pin on the ultrasonic sensor.
const int MAX_DISTANCE = 500; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Chrono timeSitting;

int sittingDistance;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(RED_PIN, OUTPUT); // initialize digital pin 13 as an output.
  pinMode(GREEN_PIN, OUTPUT); // initialize digital pin 13 as an output.
  pinMode(BLUE_PIN, OUTPUT); // initialize digital pin 13 as an output.

  sittingDistance = sonar.ping_cm(); //We are assuming the user starts in a sitting state
  timeSitting.start();
}

void loop() {
  /*
   * Read sensor 
   */
  int distance = sonar.ping_cm();
  int diff = abs(distance - sittingDistance);
  
  /*
   * Set timeSitting variable
   */
  if(diff < 10){
    //We are still sitting, do nothing
  } else {
    timeSitting.restart();
  }

  /*
   * Set lamp color
   */
  if(timeSitting.hasPassed(5000)){
    setColor(255,0,0);
  } else {
    setColor(0,255,0);
  }

  Serial.print("Current distance: "); Serial.print(distance); Serial.print(" cm. Current diff from sitting: "); Serial.print(diff); Serial.print(" cm. Has been sitting: "); Serial.print(timeSitting.elapsed()/1000);
  Serial.println(" s");
  delay(30);
}

void setColor(int red, int green, int blue){
  digitalWrite(RED_PIN, 255 - red);
  digitalWrite(GREEN_PIN, 255 - green);
  digitalWrite(BLUE_PIN, 255 - blue);
}

