#define IN1 9
#define IN2 8
#define ENA 10

enum MotorState { STOP, FORWARD, BACKWARD };

void setupMotorDriver() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Stop the motor initially
  stopMotor();
}

void setMotorState(MotorState state, int speed = 255) {
  speed = constrain(speed, 0, 255);
  analogWrite(ENA, speed); // Set speed (PWM)

  switch (state) {
    case FORWARD:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      break;
    case BACKWARD:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      break;
    case STOP:
    default:
      stopMotor();
      break;
  }
}

// Helper function to stop the motor
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// Setup function
void setup() {
  setupMotorDriver();
  Serial.begin(9600);
  Serial.println("L298N Motor Driver Initialized");
}

void loop() {
  Serial.println("Motor Forward");
  setMotorState(FORWARD, 200); 
  delay(3000);

  Serial.println("Motor Backward");
  setMotorState(BACKWARD, 200);
  delay(3000);

  Serial.println("Motor Stop");
  stopMotor();
  delay(2000);
}
