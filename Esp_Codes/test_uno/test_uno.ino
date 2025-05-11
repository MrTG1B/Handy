#include <Servo.h>  // Use the standard Arduino Servo library

int sensorPin = A0;  // select the analog input pin for the sensor (A0 for Uno)
int sensorValue = 0; // variable to store the value coming from the sensor
int servoPosition=0;

Servo myServo;       // create servo object to control a servo

void setup() {
  pinMode(sensorPin, INPUT); // declare sensor pin as input
  myServo.attach(9);         // attaches the servo on pin 9 to the servo object (adjust the pin as needed)
  
  Serial.begin(9600);        // initialize serial communication at 9600 bits per second
}

void loop() {
  // Read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  // Print the sensor value to the Serial Monitor
  Serial.println(sensorValue);

  // Optionally, you can adjust the value ranges based on your sensor's output
  // if ((sensorValue < 550) && (sensorValue > 500)) {
  //   sensorValue = 475;
  // }

  // Ensure the sensor value is within a valid range (for Arduino Uno's analog input)
  sensorValue = constrain(sensorValue, 0, 1023);

  // Map the sensor value to a range suitable for the servo (reverse mapping)
  // int servoPosition = map(sensorValue, 200, 750, 90, 180); // Adjust the range based on your sensor

  // Print sensor value and mapped servo position to the Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" - Servo Position: ");
  Serial.println(servoPosition);

  // Move the servo to the calculated position
  myServo.write(servoPosition);

  // Small delay for stability
  delay(250);
}
