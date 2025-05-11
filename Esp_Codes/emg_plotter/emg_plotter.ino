int sensorPin = 39;  // Use GPIO 34 for analog input on ESP32
int sensorValue = 0; // Variable to store the value coming from the sensor

void setup() {
  pinMode(sensorPin, INPUT); // Declare sensor pin as input
  
  Serial.begin(115200);      // Initialize serial communication at 115200 bits per second for ESP32
}

void loop() {
  // Read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  // Print the sensor value to the Serial Monitor or Serial Plotter
  Serial.println(sensorValue);

  // Small delay for stability (adjust if needed for smoother plotting)
  delay(250);
}
