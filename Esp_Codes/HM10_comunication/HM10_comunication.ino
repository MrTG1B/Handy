#include "HardwareSerial.h"

// Create a second hardware serial object for HM-10
HardwareSerial HM10(2); // Use UART2, which is GPIO16 (RX2) and GPIO17 (TX2)

void setup() {
  // Start the Serial Monitor for debugging
  Serial.begin(115200);

  // Start the serial communication with the HM-10 at 9600 baud rate
  HM10.begin(9600, SERIAL_8N1, 16, 17);  // Baud rate is 9600, RX = GPIO16, TX = GPIO17

  // Give the HM-10 some time to initialize
  delay(1000);
  
  // Send an initial message via Bluetooth to test the connection
  HM10.println("ESP32 connected to HM-10");

  Serial.println("ESP32 is ready. Type messages to send via Bluetooth.");
}

void loop() {
  // Check if data is available from HM-10 (received via Bluetooth)
  if (HM10.available()) {
    String receivedData = HM10.readString();  // Read the data
    Serial.print("Data from Bluetooth: ");
    Serial.println(receivedData);            // Display the received data on the Serial Monitor
  }

  // Check if there's data in the Serial Monitor to send via Bluetooth
  if (Serial.available()) {
    String dataToSend = Serial.readString();  // Read the data from Serial Monitor
    HM10.print(dataToSend);                  // Send the data via Bluetooth (to the connected device)
    Serial.print("Sent via Bluetooth: ");
    Serial.println(dataToSend);              // Echo the sent data back to the Serial Monitor
  }
}
