#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Servo.h>

Servo myServo;
BLECharacteristic *pCharacteristic;
const char *serviceUUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
const char *characteristicUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";

// Function prototypes
void func1();
void func2();
void func3();
void func4();
void func5();
void func6();
void func7();
void func8();

void setup() {
  Serial.begin(115200);
  
  // Initialize BLE
  BLEDevice::init("ESP32_BLE");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(serviceUUID);
  pCharacteristic = pService->createCharacteristic(
                      characteristicUUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new BLECharacteristicCallbacks());

  // Start the service
  pService->start();
  
  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(serviceUUID);
  pAdvertising->start();

  myServo.attach(9); // Attach the servo to pin 9
}

void loop() {
  // Nothing needed here, everything is handled in callbacks
}

// Callback function to handle characteristic writes
class BLECharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) override {
    String receivedValue = pCharacteristic->getValue().c_str();

    if (receivedValue.length() > 0) {
      char command = receivedValue.charAt(0);
      Serial.println("Received Value: " + receivedValue);
      
      // Control servo based on received command
      if (command == '1') func1();
      else if (command == '2') func2();
      else if (command == '3') func3();
      else if (command == '4') func4();
      else if (command == '5') func5();
      else if (command == '6') func6();
      else if (command == '7') func7();
      else if (command == '8') func8();
      else Serial.println("Invalid Command");
    }
  }
};

// Define the functions for each command
void func1() {
  Serial.println("Executing func1");
  myServo.write(0); // Rotate servo to 0 degrees
}

void func2() {
  Serial.println("Executing func2");
  myServo.write(45); // Rotate servo to 45 degrees
}

void func3() {
  Serial.println("Executing func3");
  myServo.write(90); // Rotate servo to 90 degrees
}

void func4() {
  Serial.println("Executing func4");
  myServo.write(135); // Rotate servo to 135 degrees
}

void func5() {
  Serial.println("Executing func5");
  myServo.write(180); // Rotate servo to 180 degrees
}

void func6() {
  Serial.println("Executing func6");
  // Add more servo control logic here
}

void func7() {
  Serial.println("Executing func7");
  // Add more servo control logic here
}

void func8() {
  Serial.println("Executing func8");
  // Add more servo control logic here
}
