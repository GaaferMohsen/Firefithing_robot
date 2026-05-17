/*
  ============================================
   3 Flame Sensor Direction Test (UPGRADED)
  ============================================

  Sensors:
    Left   -> A0
    Center -> A1
    Right  -> A2

  Improvements:
    - flameThreshold filtering
    - directional difference check
    - stable detection (reduces noise)
*/

const int leftSensor   = A0;
const int centerSensor = A1;
const int rightSensor  = A2;

const int relay_pin = 7;

const int flameThreshold = 500;
const int minDifference  = 30;

void setup()
{
  Serial.begin(9600);

  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);

  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW);

  Serial.println("=== Flame Sensor Test Started (UPGRADED) ===");
}

void loop()
{
  int leftValue   = analogRead(leftSensor);
  int centerValue = analogRead(centerSensor);
  int rightValue  = analogRead(rightSensor);

  Serial.print("LEFT: ");
  Serial.print(leftValue);
  Serial.print(" | CENTER: ");
  Serial.print(centerValue);
  Serial.print(" | RIGHT: ");
  Serial.println(rightValue);

  int minValue = leftValue;
  String direction = "LEFT";

  if (centerValue < minValue)
  {
    minValue = centerValue;
    direction = "CENTER";
  }

  if (rightValue < minValue)
  {
    minValue = rightValue;
    direction = "RIGHT";
  }

  int secondMin = 1023;

  if (direction != "LEFT")
    secondMin = min(secondMin, leftValue);

  if (direction != "CENTER")
    secondMin = min(secondMin, centerValue);

  if (direction != "RIGHT")
    secondMin = min(secondMin, rightValue);

  int difference = secondMin - minValue;

  if (minValue < flameThreshold && difference > minDifference)
  {
    Serial.print("Fire detected ");
    Serial.println(direction);
  }
  else
  {
    Serial.println("No stable fire detected");
  }

  Serial.println("--------------------------------");

  delay(500);
}
