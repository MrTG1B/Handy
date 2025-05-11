#define EMG_PIN 34  // Analog pin connected to the EMG sensor

// Label selection (e.g., thumb, index, middle, ring, little)
String currentLabel = "thumb"; // Start with a default label

void setup() {
  Serial.begin(115200);  // Initialize serial communication
}

void loop() {
  int emgValue = analogRead(EMG_PIN);  // Read EMG data from the sensor
  String dataLine = String(millis()) + ", " + String(emgValue) + ", " + currentLabel;
  
  // Send the data to the serial monitor
  Serial.println(dataLine);
  
  // For demonstration: Change the label every 10 seconds
  // In a real setup, you might use a button or other method to set the label
  static unsigned long lastChangeTime = 0;
  if (millis() - lastChangeTime > 10000) {  // Change label every 10 seconds
    lastChangeTime = millis();
    // Rotate through labels
    if (currentLabel == "thumb") currentLabel = "index";
    else if (currentLabel == "index") currentLabel = "middle";
    else if (currentLabel == "middle") currentLabel = "ring";
    else if (currentLabel == "ring") currentLabel = "little";
    else currentLabel = "thumb";
  }
  
  delay(10);  // Adjust the delay for desired sampling rate
}
