#include <ESP32Servo.h>   // Use the ESP32Servo library

// Servo objects
Servo servo1, servo2, servo3, servo4, servo5, servo6, servo7;

const int servoPin=13;

#define RXD2 16
#define TXD2 17
void setup() {

  servo1.attach(servoPin);
  // put your setup code here, to run once:
  Serial.begin(115200);                         // Debugging on Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // HM-10 on Serial2 (Pins 16 and 17)

  Serial.println("Waiting for Bluetooth data...");

}

void loop() {
  if (Serial2.available()) {
    char data = Serial2.read();  // Read data from HM-10 (1, 2, 3, or 4)
    Serial.println("Received data from HM-10: " + String(data));

  if (data == '1' )
  {
    servo1.write(180);
  }
  else if (data == '2')
  {
    servo1.write(0);
  }
  }
  // put your main code here, to run repeatedly:

}
