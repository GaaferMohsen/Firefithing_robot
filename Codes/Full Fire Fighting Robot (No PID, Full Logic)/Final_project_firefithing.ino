// ==========================================
//        FIRE FIGHTING ROBOT
// ==========================================

// ---------- Flame Sensors ----------
#define FLAME_SENSOR_LEFT   A0
#define FLAME_SENSOR_CENTER A1
#define FLAME_SENSOR_RIGHT  A2

// ---------- Ultrasonic ----------
#define TRIG_PIN 12
#define ECHO_PIN 13

// ---------- Relay / Pump ----------
const int relayPin = 7;

// ---------- L298N Motor Driver ----------
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

const int ENA = 5;
const int ENB = 6;

// ==========================================
// VARIABLES
// ==========================================

int motorSpeed = 120;

int flameRight;
int flameCenter;
int flameLeft;

// ==========================================
// SETUP
// ==========================================

void setup() {

  Serial.begin(9600);

  // Flame Sensors
  pinMode(FLAME_SENSOR_RIGHT, INPUT);
  pinMode(FLAME_SENSOR_CENTER, INPUT);
  pinMode(FLAME_SENSOR_LEFT, INPUT);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Relay
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Pump OFF

  // Motor Driver
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Stop();

  // ==========================================
  // STARTUP MOTOR TEST (1 SECOND)
  // ==========================================

  front();
  delay(1000);
  Stop();
}

// ==========================================
// MAIN LOOP
// ==========================================

void loop() {

  // Read flame sensors
  readFlameSensors();

  // ======================================
  // NO FIRE DETECTED
  // ======================================

  if (noFlameDetected()) {

    Stop();
    return;
  }

  // ======================================
  // FIRE ON RIGHT
  // ======================================

  if (Flame_Direction() == 1) {

    right();
    delay(100);
    Stop();
  }

  // ======================================
  // FIRE ON LEFT
  // ======================================

  else if (Flame_Direction() == 3) {

    left();
    delay(100);
    Stop();
  }

  // ======================================
  // FIRE IN CENTER
  // ======================================

  else if (Flame_Direction() == 2) {

    long distance = getDistance();

    Serial.print("Distance: ");
    Serial.println(distance);

    // ==================================
    // THE BUG FIX: STOP + SPRAY WATER
    // If the IR sensor says the fire is super close (<= 100) 
    // OR the ultrasonic sees something close... turn the pump ON!
    // ==================================

    if (flameCenter <= 100 || (distance > 0 && distance <= 15)) {
      
      Stop();

      digitalWrite(relayPin, LOW); // Pump ON
      delay(3000);

      digitalWrite(relayPin, HIGH); // Pump OFF

      Stop();
    }
    
    // ==================================
    // MOVE TOWARDS FIRE
    // ==================================
    
    else {
      front();
    }
  }
}

// ==========================================
// FLAME SENSOR FUNCTIONS
// ==========================================

void readFlameSensors() {

  flameRight  = analogRead(FLAME_SENSOR_RIGHT);
  flameCenter = analogRead(FLAME_SENSOR_CENTER);
  flameLeft   = analogRead(FLAME_SENSOR_LEFT);

  Serial.print("Left: ");
  Serial.print(flameLeft);

  Serial.print(" | Center: ");
  Serial.print(flameCenter);

  Serial.print(" | Right: ");
  Serial.println(flameRight);
}

// ==========================================

bool noFlameDetected() {

  if (flameRight > 800 &&
      flameCenter > 800 &&
      flameLeft > 800) {

    return true;
  }

  return false;
}

// ==========================================

int Flame_Direction() {

  if (flameRight < flameCenter &&
      flameRight < flameLeft) {

    return 1; // RIGHT
  }

  if (flameCenter < flameRight &&
      flameCenter < flameLeft) {

    return 2; // CENTER
  }

  if (flameLeft < flameRight &&
      flameLeft < flameCenter) {

    return 3; // LEFT
  }

  return 0;
}

// ==========================================
// ULTRASONIC FUNCTION
// ==========================================

long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  long distance = duration * 0.034 / 2;

  return distance;
}

// ==========================================
// MOVEMENT FUNCTIONS
// ==========================================

void front() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ==========================================

void back() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ==========================================

void left() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ==========================================

void right() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// ==========================================

void Stop() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
