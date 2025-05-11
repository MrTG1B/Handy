#include <Servo.h>

int index=6;
int middle=9;
int ring=10;
int pinky=11;

Servo myServo1;
// Servo myServo2;
// Servo myServo3;
// Servo myServo4; 

int servoPosition=0;

void setup() {
  myServo1.attach(index);
  // myServo2.attach(middle);
  // myServo3.attach(ring);
  // myServo4.attach(pinky);

}

void loop() {
  myServo1.write(servoPosition);
  // myServo2.write(servoPosition);
  // myServo3.write(servoPosition);
  // myServo4.write(servoPosition);

  // put your main code here, to run repeatedly:

}
