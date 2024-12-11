// Define RGB LED pins
#define RED 11
#define BLUE 10
#define GREEN 9

int mode = 0; // Current color mode
unsigned long lastChangeTime = 0;
const int changeInterval = 1000; 
void setup() {
  // Initialize LED pins as output
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  // Start with all LEDs off
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);

  Serial.begin(9600);
  Serial.println("RGB LED Mode Cycling Initialized");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastChangeTime >= changeInterval) {
    mode = (mode + 1) % 7; // Cycle through 7 modes
    lastChangeTime = currentTime;

    Serial.print("Switching to mode: ");
    Serial.println(mode);
  }

  // Set LED colors based on the current mode
  switch (mode) {
    case 0: // Red
      setColor(255, 0, 0);
      break;
    case 1: // Green
      setColor(0, 255, 0);
      break;
    case 2: // Blue
      setColor(0, 0, 255);
      break;
    case 3: // Yellow
      setColor(255, 255, 0);
      break;
    case 4: // Cyan
      setColor(0, 255, 255);
      break;
    case 5: // Magenta
      setColor(255, 0, 255);
      break;
    case 6: // White
      setColor(255, 255, 255);
      break;
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
}
