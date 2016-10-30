#include <Chrono.h>
#include <NewPing.h>

const int TRIGGER_PIN = 8;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int ECHO_PIN = 9;  // Arduino pin tied to echo pin on the ultrasonic sensor.
const int MAX_DISTANCE = 500; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;
const int BUTTON_PIN = 2;
const int PIR_PIN = 7;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Chrono timeSitting;
Chrono timeAway;

int sittingDistance;
bool isAway = false;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);

  sittingDistance = sonar.ping_cm(); //We are assuming the user starts in a sitting state
  timeSitting.start();
  timeAway.start();
}

void loop() {
  /*
   * Read all sensors 
   */
  int distance = sonar.ping_cm();
  bool presence = digitalRead(PIR_PIN);
  bool buttonPress = digitalRead(BUTTON_PIN);

   /*
   * Check is button is pressed 
   * If it is, set new sitting heigt
   */
  if (buttonPress == true) {
    sittingDistance = distance;
    timeSitting.restart();
  }

  /*
   * Set isAway variable
   */
  if (presence == true) {
    timeAway.restart();
  }

  if (timeAway.hasPassed(20000)) {
    isAway = true;
  } 
  else {
    isAway = false;
  }

  /*
   * Set timeSitting variable
   */
  int diff = abs(distance - sittingDistance);
  if(isAway == true){
    timeSitting.stop();
  }
  else if (diff < 10) {
    if(timeSitting.isRunning() == false){
      timeSitting.resume();
    }
  }
  else {
    timeSitting.restart();
  }

  /*
   * Set lamp color
   */
  if(isAway == true){
    setColor(0, 0, 0);
  }
  else if (timeSitting.hasPassed(5000)) {
    setColor(255, 0, 0);
  } 
  else {
    setColor(0, 255, 0);
  }
  Serial.print(diff); Serial.print(" , "); Serial.print(presence); Serial.print(" , ");
  Serial.println(timeSitting.elapsed());
  
  delay(30);
}

void setColor(int red, int green, int blue) {
  digitalWrite(RED_PIN, 255 - red);
  digitalWrite(GREEN_PIN, 255 - green);
  digitalWrite(BLUE_PIN, 255 - blue);
}

