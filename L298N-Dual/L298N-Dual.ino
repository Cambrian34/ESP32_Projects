// Motor A pins
#define IN1 9
#define IN2 8
#define ENA 10

// Motor B pins
#define IN3 7
#define IN4 6
#define ENB 5


//amp draw is too high, currently searching for alternative.
//only one motor  is working currently, try L298N-Single/L298N-Single.ino for usage of one motor

enum MotorState { STOP, FORWARD, BACKWARD };

void setupMotorDriver() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotorA();
  stopMotorB();
}

void setMotorAState(MotorState state, int speed = 255) {
  speed = constrain(speed, 0, 255); 
  analogWrite(ENA, speed);        
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
      stopMotorA();
      break;
  }
}

void setMotorBState(MotorState state, int speed = 255) {
  speed = constrain(speed, 0, 255); 
  analogWrite(ENB, speed);        
  switch (state) {
    case FORWARD:
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case BACKWARD:
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case STOP:
    default:
      stopMotorB();
      break;
  }
}

void stopMotorA() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

void stopMotorB() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

// Setup function
void setup() {
  setupMotorDriver();
  Serial.begin(9600);
  Serial.println("L298N Motor Driver Initialized for Motor A and Motor B");
}

void loop() {
  Serial.println("Motor A Forward, Motor B Backward");
  setMotorAState(FORWARD, 200);
  setMotorBState(BACKWARD, 200);
  delay(3000);

  Serial.println("Motor A Backward, Motor B Forward");
  setMotorAState(BACKWARD, 150);
  setMotorBState(FORWARD, 150);
  delay(3000);

  Serial.println("Stopping both motors");
  stopMotorA();
  stopMotorB();
  delay(2000);
}
