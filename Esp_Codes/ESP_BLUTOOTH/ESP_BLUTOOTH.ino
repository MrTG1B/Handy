#include <ESP32Servo.h>  // Use the ESP32Servo library

// Number of servos
const int NUM_SERVOS = 7;

// Servo array
Servo servos[NUM_SERVOS];

// Servo pins array
const int servoPins[NUM_SERVOS] = {13, 12, 14, 27, 26, 25, 33};

// Command buffer and timing
String commandBuffer = "";
unsigned long lastReceivedTime = 0;
const unsigned long commandTimeout = 100;

// Bluetooth setup (using Serial2 for communication)
#define RXD2 16
#define TXD2 17

void setup() {
  // Attach servos to their respective pins
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
  }

  // Initialize serial communication for HM-10 and debugging
  Serial.begin(115200);                        // Debugging on Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // HM-10 on Serial2 (Pins 16 and 17)
  
  // Initial swing demo
  for (int i = 0; i < NUM_SERVOS - 2; i++) {
    swing(servos[i], 0, 180, 15);
  }
  for (int i = 0; i < NUM_SERVOS - 2; i++) {
    swing(servos[i], 180, 0, 15);
  }

  Serial.println("Waiting for Bluetooth data...");
}

void loop() {
  // Check for available data from Bluetooth
  if (Serial2.available()) {
    char data = Serial2.read(); // Read incoming character
    if (isDigit(data)) {
      commandBuffer += data; // Add digit to buffer
      lastReceivedTime = millis(); // Reset the timer whenever data is received
    }
  }

  // Check if enough time has passed since last character
  if (commandBuffer.length() > 0 && (millis() - lastReceivedTime >= commandTimeout)) {
    Serial.println("Received command: " + commandBuffer);
    executeCommand(commandBuffer); // Process the buffered command
    commandBuffer = ""; // Clear buffer after processing
  }
}

void executeCommand(String command) {
  if (command == "1") func1();
  else if (command == "2") func2();
  else if (command == "3") func3();
  else if (command == "4") func4();
  else if (command == "5") func5();
  else if (command == "6") func6();
  else if (command == "7") func7();
  else if (command == "8") func8();
  // else if (command == "11") func11();
  // else if (command == "12") func12();
  else Serial.println("Unknown command received.");
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
  for (int i = 0; i < 5; i++) { swing(servos[i], 0, 90, 15); }
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
