#include "HardwareSerial.h"

// Create a second hardware serial object
HardwareSerial HM10(2);  // Use UART2, which is GPIO16 (RX2) and GPIO17 (TX2)

void setup() {
  // Start the Serial Monitor for debugging
  Serial.begin(115200);

  // Start the serial communication with the HM-10
  HM10.begin(9600, SERIAL_8N1, 16, 17);  // Baud rate is 57600, RX = GPIO16, TX = GPIO17

  delay(1000);  // Give the HM-10 some time to start

  Serial.println("Enter AT commands:");
}

void loop() {
  // If there's data available from the HM-10, print it to the Serial Monitor
  if (HM10.available()) {
    String dataFromHM10 = HM10.readString();
    Serial.print("HM-10: ");
    Serial.println(dataFromHM10);
  }

  // If there's data coming from the Serial Monitor, send it to the HM-10
  if (Serial.available()) {
    String userInput = Serial.readString();
    HM10.print(userInput);  // Send user's input to HM-10
  }
}
