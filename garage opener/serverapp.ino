// Include necessary libraries
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// GPIO pin connected to the relay
const int relayPin = 5; // Adjust according to your wiring

// Define a username and password for authentication
const char* authUsername = "admin";
const char* authPassword = "password123";

// Create a web server object on port 80
WebServer server(80);

// HTML page to control the relay
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Garage Opener</title>
</head>
<body>
  <h1>Garage Door Opener</h1>
  <button onclick="sendRequest('open')">Open/Close</button>
  <script>
    function sendRequest(action) {
      fetch(`/${action}`, {
        headers: {
          'Authorization': 'Basic ' + btoa('admin:password123')
        }
      }).then(response => {
        if (!response.ok) {
          alert('Action failed!');
        }
      });
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  // Initialize the relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Ensure relay starts in off state

  // Start serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP());

  // Define routes for the web server
  server.on("/", []() {
    if (!server.authenticate(authUsername, authPassword)) {
      return server.requestAuthentication();
    }
    server.send(200, "text/html", htmlPage);
  });

  server.on("/open", []() {
    if (!server.authenticate(authUsername, authPassword)) {
      return server.requestAuthentication();
    }
    toggleRelay();
    server.send(200, "text/plain", "OK");
  });

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}

void toggleRelay() {
  digitalWrite(relayPin, LOW); // Activate relay
  delay(1000);                 // Keep it active for 1 second
  digitalWrite(relayPin, HIGH); // Deactivate relay
  Serial.println("Relay toggled");
}
