// ==========================================
//   OBSTACLE AVOIDANCE ROBOT (7.4V Lithium)
//   Logic: "First Exit" with Organic Look-and-Turn
// ==========================================
#include <Servo.h>

// ---------- Ultrasonic Sensor (4-Pin) ----------
#define TRIG_PIN 12
#define ECHO_PIN 13

// ---------- Servo Motor ----------
Servo myservo;
const int servoPin = 3;

// ---------- L298N Motor Driver ----------
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;
const int ENA = 5;
const int ENB = 6;

// Variables
int motorSpeed = 150; 
int distance;
int select;
int pos = 0; 

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  Stop();
  delay(2000); 
}

void loop() {
  distance = getDistance();
  Serial.print("Center Distance: ");
  Serial.println(distance);

  // ==========================================
  // PHASE 1: THE CRUISE
  // ==========================================
  if (distance > 30) {
    myservo.detach(); // Ensure servo is asleep while driving straight
    front();
  }

  // ==========================================
  // PHASE 2: THE PANIC STOP & SWEEP
  // ==========================================
  else if (distance > 0 && distance <= 30) {
    Stop();      
    delay(200);  
    
    myservo.attach(servoPin); // Wake up servo

    while (distance <= 30) {
      myservo.write(pos);
      delay(300); 
      distance = getDistance();
      
      if (distance > 30) {
        select = pos;
        break; 
      }
      
      pos += 45;
      if (pos == 90) pos = 135; 
      if (pos > 180) pos = 0; 
    }

    // ==========================================
    // PHASE 3: THE ESCAPE (Organic Look-and-Turn)
    // ==========================================
    
    // 1. Notice we do NOT center the servo yet! 
    // It stays locked on the 'select' angle, staring exactly where we want to go.

    // 2. Execute the escape turn with the chassis
    switch (select) {
      case 0:
        right(); delay(400); Stop(); break;
      case 45:
        right(); delay(250); Stop(); break;
      case 135:
        left(); delay(250); Stop(); break;
      case 180:
        left(); delay(400); Stop(); break;
    }
    
    // 3. The body has finished turning to face the exit. 
    // NOW we snap the head (servo) back to the center!
    myservo.write(90);
    delay(300); // Give the gears time to physically move back
    
    // 4. Everything is aligned. Put the servo to sleep!
    myservo.detach(); 

    pos = 0; 
  }
}

// ==========================================
// UTILITY FUNCTIONS
// ==========================================

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  
  if (duration == 0) return 999; 
  
  return duration * 0.034 / 2;
}

void front() {
  analogWrite(ENA, motorSpeed); analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void back() {
  analogWrite(ENA, motorSpeed); analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void left() {
  analogWrite(ENA, motorSpeed); analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  analogWrite(ENA, motorSpeed); analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void Stop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0);
}