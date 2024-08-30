#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of the web server
WebServer server(80);

// Define the pin connected to the relay
const int relayPin = 23;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Ensure relay is off initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Define HTTP request handlers
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleRelayOn);
  server.on("/off", HTTP_GET, handleRelayOff);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

// Handle root URL
void handleRoot() {
  server.send(200, "text/html", "<h1>ESP32 Smart Plug</h1><p><a href=\"/on\">Turn On</a></p><p><a href=\"/off\">Turn Off</a></p>");
}

// Handle relay on request
void handleRelayOn() {
  digitalWrite(relayPin, HIGH);  // Turn relay on
  server.send(200, "text/html", "<h1>Relay is ON</h1><p><a href=\"/\">Back</a></p>");
}

// Handle relay off request
void handleRelayOff() {
  digitalWrite(relayPin, LOW);  // Turn relay off
  server.send(200, "text/html", "<h1>Relay is OFF</h1><p><a href=\"/\">Back</a></p>");
}
