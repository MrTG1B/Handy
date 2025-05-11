#include <ESP32Servo.h>  // Use the ESP32Servo library
#include "HardwareSerial.h"

// Create a second hardware serial object for HM-10
HardwareSerial HM10(2); // Use UART2, which is GPIO16 (RX2) and GPIO17 (TX2)

// Number of servos
const int NUM_SERVOS = 8;

// Servo array
Servo servos[NUM_SERVOS];

// Servo pins array
const int servoPins[NUM_SERVOS] = {13, 12, 14, 27, 26, 25, 33, 15}; // 8th servo on pin 15

// FSR and Motor Pins
const int numFSRs = 4;
const int fsrPins[numFSRs] = {32, 35, 34, 36};     // FSR pins array
const int motorPins[numFSRs] = {4, 5, 18, 19};     // Motor pins array

// EMG sensor pin and threshold
const int emgPin = 39;
const int emgThreshold = 3000;

// Thresholds
const int fsrThreshold = 500;  // Adjust based on your FSR sensitivity

//wrist angle
int wristSwingAngle=90;
int wristRotateAngle=90;

// Bluetooth setup (using Serial2 for communication)
#define RXD2 16
#define TXD2 17

bool commandExecuted = false;

String commandData="";

typedef void (*CommandFunction)();

void setup() {
  // Attach servos to their respective pins
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
  }

  // Initialize motor pins as outputs
  for (int i = 0; i < numFSRs; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);  // Start with motors off
  }

  // Initialize EMG pin as input
  pinMode(emgPin, INPUT);

  // Initialize serial communication for HM-10 and debugging
  Serial.begin(115200);                        // Debugging on Serial Monitor
  HM10.begin(9600, SERIAL_8N1, RXD2, TXD2); // HM-10 on Serial2 (Pins 16 and 17)

  Serial.println("Waiting for Bluetooth data...");
}

void loop() {
  // Check for available data from Bluetooth
  if (HM10.available()) {
    commandData = HM10.readString(); // Read incoming character
    Serial.println("Stored command: " + commandData); 
    if ((commandData=="9")||(commandData=="10")||(commandData=="11")||(commandData=="12"))
    {
      executeCommand(commandData);
    }
  }

  // Handle FSR readings and control vibration motors
  for (int i = 0; i < numFSRs; i++) {
    int fsrValue = analogRead(fsrPins[i]);

    // Map FSR values to motor intensity (0-255 for PWM control)
    int motorIntensity = map(fsrValue, fsrThreshold, 4095, 0, 255); // Adjust 4095 if using a 10-bit ADC
    motorIntensity = constrain(motorIntensity, 0, 255); // Constrain to valid PWM range

    analogWrite(motorPins[i], motorIntensity); // Set motor intensity based on FSR value
  }
  
  // Check EMG data
  checkEmgData();
  delay(500);
}

void checkEmgData() {
  // int emgData = analogRead(emgPin);
  // Serial.println(emgData);
  // if (emgData > emgThreshold) {
  if (digitalRead(emgPin)==HIGH){
    if (commandExecuted==false) {
      executeCommand(commandData);
      commandExecuted = true;
      Serial.println("commandExecuted");
      
    } else if (commandExecuted==true) {
      openAllServos();
      commandExecuted = false;  // Reset for the next command
    }
  }
}

void openAllServos() {
  for (int i = 0; i < 5; i++) {  // Only set the first five servos
    servos[i].write(0);  // Set each of the first five servos to 0 degrees
  }
  for (int i=5;i<NUM_SERVOS;i++){
    servos[i].write(90);
  }
  Serial.println("First five servos opened to 0 degrees.");
}

void swing(Servo &myServo, int startPos, int endPos, int delayTime) {
  if (startPos < endPos) {
    for (int pos = startPos; pos <= endPos; pos++) {
      myServo.write(pos);
      delay(delayTime);
    }
  } else {
    for (int pos = startPos; pos >= endPos; pos--) {
      myServo.write(pos);
      delay(delayTime);
    }
  }
}

// Command functions
void func1() {
  for (int i = 0; i < 5; i++) { servos[i].write(90); }
  servos[5].write(90); // Wrist swing
  servos[6].write(0);  // Wrist rotate
}

void func2() {
  servos[0].write(0); 
  for (int i = 1; i < 5; i++) { servos[i].write(180); }
  servos[5].write(90); // Wrist swing
  servos[6].write(0);  // Wrist rotate
}

void func3() {
  servos[0].write(180); 
  servos[1].write(45);
  servos[2].write(90);
  servos[3].write(135);
  servos[4].write(180);
  servos[5].write(90); // Wrist swing
  servos[6].write(90); // Wrist rotate
}

void func4() {
  servos[0].write(180);
  for (int i = 1; i < 5; i++) { servos[i].write(30); }
  servos[5].write(0);  // Wrist swing
  servos[6].write(0);  // Wrist rotate
}

void func5() {
  for (int i = 0; i < 5; i++) { servos[i].write(180); }
  servos[5].write(90); // Wrist swing
  servos[6].write(90); // Wrist rotate
}

void func6() {
  for (int i = 0; i < 5; i++) { servos[i].write(180); }
  servos[5].write(90); // Wrist swing
  servos[6].write(90); // Wrist rotate
}

void func7() {
  for (int i = 0; i < 5; i++) { servos[i].write(180); }
  servos[5].write(90); // Wrist swing
  servos[6].write(90); // Wrist rotate
}

void func8() {
  for (int i = 0; i < 5; i++) { servos[i].write(180); }
  servos[5].write(90); // Wrist swing
  servos[6].write(90); // Wrist rotate
}

void func9(){
  wristSwingAngle=wristSwingAngle+90;
  servos[5].write(wristSwingAngle);
}

void func10(){
  wristSwingAngle=wristSwingAngle-90;
  servos[5].write(wristSwingAngle);
}

void func11(){
  wristRotateAngle=wristRotateAngle+90;
  servos[6].write(wristRotateAngle);
}

void func12(){
  wristRotateAngle=wristRotateAngle-90;
  servos[6].write(wristRotateAngle);
}

void func13(){
  servos[0].write(180);
  servos[2].write(180);
  servos[3].write(180);
  servos[1].write(0);
  servos[4].write(0);
}

void func14(){
  for(int i=0;i<5;i++)
  {
    servos[i].write(180);
  }
  delay(100);
  servos[2].write(0);
}



// Array of function pointers
CommandFunction functions[] = {
  func1, func2, func3, func4, func5, func6, func7,
  func8, func9, func10, func11, func12, func13, func14
};


void executeCommand(String command) {
  int index = command.toInt();  // Convert string to integer
  // Note: In Arduino, use sizeof(functions)/sizeof(functions[0]) instead of .length()
  if (index >= 1 && index <= sizeof(functions)/sizeof(functions[0])) {
    functions[index - 1]();  // Arrays are 0-based, so subtract 1
  } else {
    Serial.println("Unknown command received.");
  }
  // commandData="";
}
