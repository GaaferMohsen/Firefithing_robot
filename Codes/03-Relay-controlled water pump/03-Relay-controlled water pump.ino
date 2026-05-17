// -------------------- PIN SETUP --------------------
const int flame1 = A0;
const int flame2 = A1;
const int flame3 = A2;

const int relayPin = 7;

// Adjust this threshold based on your sensor readings
// LOWER value often means fire detected (depends on module)
int fireThreshold = 500;

// -------------------- SETUP --------------------
void setup() {
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH); // Relay OFF (most relays are active LOW)

  Serial.begin(9600);
}

// -------------------- FUNCTION: CHECK FIRE --------------------
bool isFireDetected() {
  int f1 = analogRead(flame1);
  int f2 = analogRead(flame2);
  int f3 = analogRead(flame3);

  Serial.print("F1: "); Serial.print(f1);
  Serial.print(" F2: "); Serial.print(f2);
  Serial.print(" F3: "); Serial.println(f3);

  // Fire detected if ANY sensor goes below threshold
  if (f1 < fireThreshold || f2 < fireThreshold || f3 < fireThreshold) {
    return true;
  }
  return false;
}

// -------------------- LOOP --------------------
void loop() {

  if (isFireDetected()) {

    // FIRE DETECTED → START PUMP CYCLE
    while (isFireDetected()) {

      // TURN PUMP ON
      digitalWrite(relayPin, LOW);   // Relay ON
      delay(3000);

      if (!isFireDetected()) break;

      // TURN PUMP OFF
      digitalWrite(relayPin, HIGH);  // Relay OFF
      delay(3000);
    }

    // Ensure pump is OFF when fire disappears
    digitalWrite(relayPin, HIGH);
  }
  else {
    // NO FIRE → KEEP PUMP OFF
    digitalWrite(relayPin, HIGH);
  }

  delay(200); // small stability delay
}