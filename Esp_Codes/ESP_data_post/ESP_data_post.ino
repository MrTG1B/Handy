#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DASGUPTA";
const char* password = "Probhaboti@2022";
const char* serverName = "https://6883cjlh-8080.inc1.devtunnels.ms/";  // Server URL

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);  // Specify the server URL
    
    http.addHeader("Content-Type", "application/json");  // Define the request type
    String postData = "{\"temperature\": 25.5, \"humidity\": 60}";  // Example data to post
    
    int httpResponseCode = http.POST(postData);  // Send HTTP POST request

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response
      Serial.println(httpResponseCode);   // Print the response code
      Serial.println(response);           // Print the response
    } else {
      Serial.print("Error in sending POST: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();  // End HTTP connection
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(1000);  // Delay between requests (e.g., 10 seconds)
}
