#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DASGUPTA";          // Your Wi-Fi SSID
const char* password = "Probhaboti@2022";  // Your Wi-Fi Password
const char* serverName = "https://emg-server.netlify.app/.netlify/functions/post-data"; // Your Netlify function URL

String valueToSend;  // Variable to store user input

void setup() {
  Serial.begin(115200);     // Start the Serial Monitor
  WiFi.begin(ssid, password);  // Connect to Wi-Fi

  // Wait for connection to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Please enter a value to send:");
}

void loop() {
  // Wait for user input in the Serial Monitor
  // if (Serial.available() > 0) {
    // Read the value entered by the user
    valueToSend ="45666";
    valueToSend.trim();  // Remove any leading/trailing spaces or new lines
    
    // Call the function to send data to the server
    sendData(valueToSend);
    
    // Ask for next input after sending data
    // Serial.println("Please enter another value to send:");
  // }
}

void sendData(String value) {
  if (WiFi.status() == WL_CONNECTED) {   // Check Wi-Fi connection status
    HTTPClient http;

    http.begin(serverName);              // Specify the URL for the Netlify serverless function
    http.addHeader("Content-Type", "application/json");  // Set the content type to JSON

    // Create JSON data string from user input
    String jsonData = "{\"value\":\"" + value + "\"}";

    // Send the HTTP POST request
    int httpResponseCode = http.POST(jsonData);

    // Handle the response from the server
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println("Server response: " + response);
    } else {
      Serial.print("Error in sending POST request, code: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close the connection
  } else {
    Serial.println("Error: WiFi not connected");
  }
}
