/*
4-Wheel Robot Test using Arduino + L298N
*/

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

const int ENA = 5;
const int ENB = 6;

const int relay_pin = 7; // Reserved for water pump

int motorSpeed = 200;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  delay(2000);

  moveForward();
  delay(3000);
  stopMotors();
  delay(1000);

  moveBackward();
  delay(3000);
  stopMotors();
  delay(1000);

  turnLeft();
  delay(3000);
  stopMotors();
  delay(1000);

  turnRight();
  delay(3000);
  stopMotors();
  delay(2000);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    moveForward();
    delay(3000);

    stopMotors();
    delay(500);

    turnLeft();
    delay(700);

    stopMotors();
    delay(500);
  }

  stopMotors();

  while (true);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
