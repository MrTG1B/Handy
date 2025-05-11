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
    http.begin(serverName);  // Specify the URL

    int httpResponseCode = http.GET();  // Send HTTP GET request

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response payload
      Serial.println(httpResponseCode);   // Print the HTTP response code
      Serial.println(response);           // Print the received data
    } else {
      Serial.print("Error in HTTP GET: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();  // End HTTP connection
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(1000);  // Delay between GET requests (e.g., 10 seconds)
}
