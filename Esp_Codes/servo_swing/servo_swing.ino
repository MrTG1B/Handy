#include <ESP32Servo.h>  // Include the ESP32Servo library

Servo myServo;  // Create a Servo object

void setup() {
  myServo.attach(13);  // Attach the servo to pin 13 (change to the pin you're using)
}

void loop() {
  // Move from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);  // Set the servo position
    delay(15);  // Wait for the servo to reach the position
  }
  
  // Move from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);  // Set the servo position
    delay(15);  // Wait for the servo to reach the position
  }
}
