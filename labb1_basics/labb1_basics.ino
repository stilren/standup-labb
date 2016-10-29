void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(13, OUTPUT); // initialize digital pin 13 as an output.
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Tänd");  // print out text
  delay(1000);             // wait for a second
  digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("Släck");
  delay(1000);              // wait for a second
}
