// --------------------
// Fire Detection Robot
// Arduino UNO + L298N + 3 Flame Sensors
// --------------------

// Motor pins
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Flame sensors
#define LEFT_SENSOR   A0
#define CENTER_SENSOR A1
#define RIGHT_SENSOR  A2

// Flame detection threshold
int threshold = 500;

// --------------------
// MOTOR FUNCTIONS
// --------------------

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// --------------------
// STARTUP MOVEMENT
// --------------------

void startupMove() {

  // Move forward for 3 seconds
  moveForward();
  delay(3000);

  // Small scan turn
  turnLeft();
  delay(300);

  stopMotors();
}

// --------------------
// SETUP
// --------------------

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  stopMotors();

  // Initial movement
  startupMove();
}

// --------------------
// MAIN LOOP
// --------------------

void loop() {

  // Read sensors
  int left   = analogRead(LEFT_SENSOR);
  int center = analogRead(CENTER_SENSOR);
  int right  = analogRead(RIGHT_SENSOR);

  // Debug output
  Serial.print("Left: ");
  Serial.print(left);

  Serial.print("  Center: ");
  Serial.print(center);

  Serial.print("  Right: ");
  Serial.println(right);

  // Detect fire
  bool fireDetected =
      (left < threshold) ||
      (center < threshold) ||
      (right < threshold);

  // --------------------
  // NO FIRE
  // --------------------

  if (!fireDetected) {

    stopMotors();
  }

  // --------------------
  // FIRE ON LEFT
  // --------------------

  else if (left < center && left < right) {

    turnLeft();
  }

  // --------------------
  // FIRE ON RIGHT
  // --------------------

  else if (right < center && right < left) {

    turnRight();
  }

  // --------------------
  // FIRE IN CENTER
  // --------------------

  else {

    moveForward();
  }

  delay(100);
}