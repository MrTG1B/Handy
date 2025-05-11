const int fsrPin1 = 32;
const int fsrPin2 = 35;
const int fsrPin3 = 34;
const int fsrPin4 = 36;
const int fsrThreshold = 500;  // Adjust based on your FSR sensitivity

// Vibration motor pins
const int motorPin1 = 16;
const int motorPin2 = 17;
const int motorPin3 = 18;
const int motorPin4 = 19;

void setup() {
  // Initialize motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Start with motors off
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  // Initialize Serial Communication
  Serial.begin(115200);
}

void loop() {
  // Read FSR values
  int fsrValue1 = analogRead(fsrPin1);
  int fsrValue2 = analogRead(fsrPin2);
  int fsrValue3 = analogRead(fsrPin3);
  int fsrValue4 = analogRead(fsrPin4);

  // Print FSR values to the Serial Monitor
  Serial.print("FSR1: ");
  Serial.print(fsrValue1);
  Serial.print(" | FSR2: ");
  Serial.print(fsrValue2);
  Serial.print(" | FSR3: ");
  Serial.print(fsrValue3);
  Serial.print(" | FSR4: ");
  Serial.println(fsrValue4);

  // Control motors based on FSR readings
  digitalWrite(motorPin1, (fsrValue1 > fsrThreshold) ? HIGH : LOW);
  digitalWrite(motorPin2, (fsrValue2 > fsrThreshold) ? HIGH : LOW);
  digitalWrite(motorPin3, (fsrValue3 > fsrThreshold) ? HIGH : LOW);
  digitalWrite(motorPin4, (fsrValue4 > fsrThreshold) ? HIGH : LOW);

  // Add delay to slow down loop execution
  delay(500);
}
