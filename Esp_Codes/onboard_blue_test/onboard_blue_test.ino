#include "BluetoothSerial.h" // Include the Bluetooth Serial library

BluetoothSerial ESP_BT;  // Create a BluetoothSerial object

void setup() {
  // Start Serial Monitor for debugging at 115200 baud rate
  Serial.begin(115200);
  
  // Start Bluetooth with a custom name
  ESP_BT.begin("ESP32_Test"); // Name your ESP32 Bluetooth
  
  // Wait a bit for things to settle
  delay(1000);
  
  Serial.println("Bluetooth Device is Ready to Pair");
}

void loop() {
  // Check if Bluetooth is connected and available
  if (ESP_BT.available()) {
    // Read incoming Bluetooth data
    char incomingChar = ESP_BT.read();
    
    // Print the received data on the Serial Monitor
    Serial.print("Received: ");
    Serial.println(incomingChar);
    
    // Echo the data back via Bluetooth
    ESP_BT.write(incomingChar);
  }

  // Send data to Bluetooth when Serial Monitor input is detected
  if (Serial.available()) {
    // Read from the serial monitor
    char serialData = Serial.read();
    
    // Send this data via Bluetooth
    ESP_BT.write(serialData);
    
    // Print on the Serial Monitor
    Serial.print("Sent: ");
    Serial.println(serialData);
  }
}
