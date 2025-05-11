#include <ESP32Servo.h>  // Use the ESP32Servo library
#include "HardwareSerial.h"

// Create a second hardware serial object for HM-10
HardwareSerial HM10(2); // Use UART2, which is GPIO16 (RX2) and GPIO17 (TX2)

// Number of servos
const int NUM_SERVOS = 8;

// Servo array
Servo servos[NUM_SERVOS];

// Servo pins array
//13=Index=1
//12=Middle=2
//14=Ring=3
//27=Small=4
//26=Thumb Rotate=5
//25=Thumb=6
const int servoPins[NUM_SERVOS] = {13, 12, 14, 27, 26, 25, 33, 15}; // 8th servo on pin 15

// FSR and Motor Pins
const int numFSRs = 4;
const int fsrPins[numFSRs] = {32, 35, 34, 36};     // FSR pins array
const int motorPins[numFSRs] = {4, 5, 18, 19};     // Motor pins array

// EMG sensor pin and threshold
const int emgPin = 39;
const int emgThreshold = 1000;

// High-pass filter settings
float alpha = 0.95;  // Adjust alpha to control cutoff frequency (0 < alpha < 1)
int previousEmg = 0; // Store previous EMG reading
int filteredEmg = 0; // Store filtered EMG value

// Thresholds
const int fsrThreshold = 500;  // Adjust based on your FSR sensitivity


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
  servos[4].write(90);

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
    Serial.println(fsrValue);

    // Adjust the mapping if using a 10-bit ADC
    int motorIntensity = map(fsrValue, fsrThreshold, 1023, 0, 255); // Adjusting for 10-bit ADC range (0-1023)
    motorIntensity = constrain(motorIntensity, 0, 255); // Constrain to valid PWM range

    analogWrite(motorPins[i], motorIntensity); // Set motor intensity based on FSR value
}
  
  // Check EMG data
  checkEmgData();
  delay(500);
}

void checkEmgData() {
  int currentEmg = analogRead(emgPin);

  filteredEmg = alpha * (filteredEmg + currentEmg - previousEmg);
  filteredEmg=constrain(filteredEmg,0,4095);
  previousEmg = currentEmg; // Update previous reading for the next iteration

  // Serial.println(filteredEmg);

  if (filteredEmg > emgThreshold) {
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
  for (int i = 0; i < 4; i++) {  // Only set the first five servos
    servos[i].write(180);  // Set each of the first five servos to 0 degrees
  }
  servos[4].write(90);
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
  for (int i = 0; i < 4; i++) { servos[i].write(90); }
}

void func2() {
  for (int i = 0; i < 4; i++) { servos[i].write(0); }
  servos[4].write(180);
}

void func3() {
  servos[0].write(135);
  servos[1].write(90);
  servos[2].write(45);
  servos[3].write(0);
  servos[4].write(0);
}

void func4() {
  for (int i = 0; i < 4; i++) { servos[i].write(150); }
  servos[4].write(0);
}

void func5() {
  for (int i = 0; i < 4; i++) { servos[i].write(0); }
  servos[4].write(0);
}

void func6() {
  for (int i = 0; i < 5; i++) { servos[i].write(180); }
}

void func7() {
  for (int i = 0; i < 5; i++) { servos[i].write(0); }
}

void func8() {
  for (int i = 0; i < 5; i++) { servos[i].write(0); }
}

void func9(){
  servos[1].write(0);
  servos[2].write(0);
  servos[0].write(180);
  servos[3].write(180);
  servos[4].write(90);
}

void func10(){
  for(int i=0;i<4;i++){servos[i].write(0);}
  servos[4].write(90);
}

void func11(){
  for(int i=0;i<5;i++)
  {
    servos[i].write(0);
  }
  delay(1000);
  servos[1].write(180);
}


// Array of function pointers
CommandFunction functions[] = {
  func1, func2, func3, func4, func5, func6, func7,
  func8, func9, func10, func11
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
