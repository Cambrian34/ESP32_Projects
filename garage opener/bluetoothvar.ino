#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// GPIO pin connected to the relay
const int relayPin = 5; // Adjust according to your wiring

// Define Bluetooth credentials
const char* deviceName = "ESP32_GarageOpener";
const char* authPassword = "1234"; // Optional PIN for pairing

void setup() {
  // Initialize the relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Ensure relay starts in off state

  // Start serial communication
  Serial.begin(115200);

  // Initialize Bluetooth with a device name
  SerialBT.begin(deviceName); // Uncomment this line to require pairing PIN: SerialBT.begin(deviceName, true);
  Serial.println("Bluetooth device is ready to pair");

  if (authPassword != nullptr) {
    SerialBT.setPin(authPassword); // Set pairing PIN
  }
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim(); // Remove any whitespace or newline characters

    if (command == "OPEN") {
      toggleRelay();
      SerialBT.println("Garage door toggled.");
    } else {
      SerialBT.println("Invalid command. Use 'OPEN' to toggle the garage door.");
    }
  }
}

void toggleRelay() {
  digitalWrite(relayPin, LOW); // Activate relay
  delay(1000);                 // Keep it active for 1 second
  digitalWrite(relayPin, HIGH); // Deactivate relay
  Serial.println("Relay toggled");
}
