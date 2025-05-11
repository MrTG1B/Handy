#include <WiFi.h>
#include <ESP32Servo.h>  // Use the ESP32Servo library instead of the standard Servo library

// Wi-Fi credentials
const char* ssid = "Tirthankar";
const char* password = "Dasgupta2004";

// Servo objects
Servo servo1, servo2, servo3, servo4, servo5, servo6, servo7;

// Servo pins
const int servoPin1 = 13;
const int servoPin2 = 12;
const int servoPin3 = 14;
const int servoPin4 = 27;
const int servoPin5 = 26;
const int servoPin6 = 25;
const int servoPin7 = 33;

// FSR pins (Analog inputs)
const int fsrPin1 = 32;
const int fsrPin2 = 35;
const int fsrPin3 = 34;
const int fsrPin4 = 36;

// Vibration motor pins (Reassigned to different pins)
const int motorPin1 = 4;  // Changed from 16 to 4
const int motorPin2 = 5;  // Changed from 17 to 5
const int motorPin3 = 18;
const int motorPin4 = 19;

// FSR threshold for motor activation
const int fsrThreshold = 500;  // Adjust based on your FSR sensitivity

WiFiServer server(80);  // Initialize the server on port 80

// Bluetooth communication using HM-10 module on pins 16 (RX) and 17 (TX)
HardwareSerial BTSerial(2);  // Use UART2 for Bluetooth (RX on 16, TX on 17)

void setup() {
  // Initialize servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
  servo6.attach(servoPin6);
  servo7.attach(servoPin7);

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

  // Connect to Wi-Fi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print IP address
  Serial.print("Connected to WiFi. IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();

  // Initialize HM-10 Bluetooth communication
  BTSerial.begin(9600, SERIAL_8N1, 16, 17);  // Baud rate: 9600, RX: 16, TX: 17
  Serial.println("Bluetooth module ready");
}

void loop() {
  // Handle incoming client requests (via WiFi)
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Parse the incoming request (e.g., "servo1:90")
    if (request.startsWith("servo1:")) {
      int angle = request.substring(7).toInt();
      servo1.write(angle);
    } else if (request.startsWith("servo2:")) {
      int angle = request.substring(7).toInt();
      servo2.write(angle);
    } else if (request.startsWith("servo3:")) {
      int angle = request.substring(7).toInt();
      servo3.write(angle);
    } else if (request.startsWith("servo4:")) {
      int angle = request.substring(7).toInt();
      servo4.write(angle);
    } else if (request.startsWith("servo5:")) {
      int angle = request.substring(7).toInt();
      servo5.write(angle);
    } else if (request.startsWith("servo6:")) {
      int angle = request.substring(7).toInt();
      servo6.write(angle);
    } else if (request.startsWith("servo7:")) {
      int angle = request.substring(7).toInt();
      servo7.write(angle);
    }

    // Send a proper HTTP response to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");  // The connection will be closed after completion of the response
    client.println();  // Empty line to indicate the end of headers
    client.println("Command received");

    delay(1);  // Allow time for the client to receive the data
    client.stop();  // Close the connection
  }

  // Handle FSR readings and control vibration motors
  int fsrValue1 = analogRead(fsrPin1);
  int fsrValue2 = analogRead(fsrPin2);
  int fsrValue3 = analogRead(fsrPin3);
  int fsrValue4 = analogRead(fsrPin4);

  digitalWrite(motorPin1, (fsrValue1 > fsrThreshold) ? HIGH : LOW);
  digitalWrite(motorPin2, (fsrValue2 > fsrThreshold) ? HIGH : LOW);
  digitalWrite(motorPin3, (fsrValue3 > fsrThreshold) ? HIGH : LOW);
  digitalWrite(motorPin4, (fsrValue4 > fsrThreshold) ? HIGH : LOW);

  delay(100);  // Small delay for stability

  // Bluetooth communication handling
  if (BTSerial.available()) {
    String btCommand = BTSerial.readStringUntil('\n');
    btCommand.trim();  // Remove any trailing newline characters

    Serial.print("Received via Bluetooth: ");
    Serial.println(btCommand);

    // Handle Bluetooth commands to control servos, motors, or other components
    if (btCommand.startsWith("servo1:")) {
      int angle = btCommand.substring(7).toInt();
      servo1.write(angle);
    } else if (btCommand.startsWith("servo2:")) {
      int angle = btCommand.substring(7).toInt();
      servo2.write(angle);
    } else if (btCommand.startsWith("servo3:")) {
      int angle = btCommand.substring(7).toInt();
      servo3.write(angle);
    } else if (btCommand.startsWith("servo4:")) {
      int angle = btCommand.substring(7).toInt();
      servo4.write(angle);
    } else if (btCommand.startsWith("servo5:")) {
      int angle = btCommand.substring(7).toInt();
      servo5.write(angle);
    } else if (btCommand.startsWith("servo6:")) {
      int angle = btCommand.substring(7).toInt();
      servo6.write(angle);
    } else if (btCommand.startsWith("servo7:")) {
      int angle = btCommand.substring(7).toInt();
      servo7.write(angle);
    }
  }
}
