#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "DASGUPTA";
const char* password = "Probhaboti@2022";
const char* serverName = "https://emg-server.netlify.app/.netlify/functions/get-data";

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

    http.begin(serverName);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.println("Error in GET request");
    }

    http.end();
  }

  delay(2000);
  // put your main code here, to run repeatedly:
}
