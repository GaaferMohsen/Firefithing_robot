# Autonomous Firefighting Robot

A beginner-friendly autonomous robot that detects fire using flame sensors and extinguishes it with a water pump, powered by an Arduino UNO.

---

# Table of Contents

1. Project Overview
2. Features
3. Components List
4. How It Works
5. Circuit Diagram
6. Folder Structure
7. Pin Connections
8. PID Control Explanation
9. Code Development Stages
10. How to Upload and Run
11. Safety Notes
12. Troubleshooting
13. Mechanical Design
14. Future Improvements
15. License
16. Author

---

# Project Overview

Firefighting Robot is a fully autonomous robot designed for learning robotics, embedded systems, and sensor integration using Arduino.

The robot can:

- Move using four DC motors
- Detect flames from multiple directions
- Navigate toward fire
- Avoid obstacles using ultrasonic sensing
- Activate a water pump to extinguish fire
- Resume searching after the fire is gone

The project is organized in stages so beginners can test and understand each subsystem independently before running the full robot.

---

# Features

- Autonomous fire detection
- Automatic fire extinguishing
- Obstacle avoidance
- Multi-direction flame sensing
- Arduino UNO based control system
- Relay-controlled water pump
- Modular step-by-step code structure
- Beginner-friendly documentation
- Expandable architecture for future upgrades

---

# Components List

| Component | Quantity | Purpose |
|---|---|---|
| Arduino UNO | 1 | Main controller |
| L298N Motor Driver | 1 | Controls DC motors |
| DC Motors with Wheels | 4 | Robot movement |
| Flame Sensors | 4 | Detect fire |
| HC-SR04 Ultrasonic Sensor | 1 | Detect obstacles |
| Relay Module | 1 | Controls pump power |
| Mini Water Pump | 1 | Sprays water |
| 12V Battery | 1 | Powers motors |
| 3.7V Battery | 1 | Powers water pump |
| Breadboard | 1 | Power distribution |
| Jumper Wires | Multiple | Electrical connections |
| Robot Chassis | 1 | Mechanical structure |

---

# Component Explanations

## Arduino UNO

Acts as the main controller. It reads sensor data, processes decisions, and controls the motors and water pump.

## L298N Motor Driver

The Arduino cannot directly power motors because motors require more current than the board can safely provide. The L298N driver acts as an interface between the Arduino and the motors.

## Flame Sensors

Infrared flame sensors detect fire by sensing infrared light emitted from flames. They output LOW when fire is detected and HIGH otherwise.

## Ultrasonic Sensor

Measures distance using sound waves. It helps the robot avoid collisions with walls or obstacles.

## Relay Module

Acts as an electronically controlled switch for the water pump.

---

# How It Works

## System Workflow

```text
Robot Starts
     ↓
Search for Fire
     ↓
Fire Detected?
   /     \
 YES      NO
  ↓        ↓
Move      Continue Searching
Toward
Fire
  ↓
Obstacle Detected?
   /     \
 YES      NO
  ↓        ↓
Avoid     Continue
Obstacle  Forward
  ↓
Close to Fire?
     ↓
Stop Robot
     ↓
Activate Water Pump
     ↓
Fire Gone?
   /     \
 NO       YES
  ↓         ↓
Continue   Turn Off Pump
Pumping        ↓
           Resume Search
```

---

# Circuit Diagram

Add your wiring diagram images here.

```md
images/circuit/circuit_diagram.png
images/circuit/circuit_sketch.jpg
```

---

# Folder Structure

```text
Firefighting_Robot/
│
├── README.md
│
├── code/
│   ├── 01-Motor_Test/
│   ├── 02-Flame_Sensor_Test/
│   ├── 03-Relay_Water_Pump/
│   ├── 04-Obstacle_Ultrasonic/
│   ├── 05-Fire_Chaser/
│   ├── 06-Fire_Fusion_Sonar/
│   └── Final_Project/
│
├── hardware/
│   ├── pin_connections.md
│   └── components.md
│
├── docs/
│   ├── how_it_works.md
│   ├── pid_explained.md
│   └── build_guide.md
│
└── images/
    ├── circuit/
    ├── robot/
    └── diagrams/
```

---

# Pin Connections

## Flame Sensors

| Sensor | Arduino Pin |
|---|---|
| Front Flame Sensor | A0 |
| Left Flame Sensor | A1 |
| Right Flame Sensor | A2 |
| Back Flame Sensor | A3 |

## Ultrasonic Sensor

| HC-SR04 Pin | Arduino Pin |
|---|---|
| TRIG | D7 |
| ECHO | D8 |

## Motor Driver (L298N)

| L298N Pin | Arduino Pin |
|---|---|
| IN1 | D2 |
| IN2 | D3 |
| IN3 | D4 |
| IN4 | D5 |
| ENA | D9 |
| ENB | D10 |

## Relay Module

| Relay Pin | Arduino Pin |
|---|---|
| Signal | D12 |

---

# Power System Notes

- Motors are powered separately using the 12V battery through the L298N.
- The water pump uses a separate 3.7V battery.
- All grounds must be connected together.
- Avoid powering motors directly from the Arduino board.

---

# PID Control Explanation

PID control helps the robot steer smoothly toward fire.

## PID Terms

| Term | Meaning |
|---|---|
| P (Proportional) | Reacts to current error |
| I (Integral) | Corrects long-term drift |
| D (Derivative) | Reduces overshoot |

## Example PID Code

```cpp
float Kp = 1.5;
float Ki = 0.0;
float Kd = 0.5;

float error = leftSensor - rightSensor;

float correction =
    Kp * error +
    Kd * (error - lastError);

leftMotorSpeed  = baseSpeed + correction;
rightMotorSpeed = baseSpeed - correction;
```

---

# Code Development Stages

| Stage | Description |
|---|---|
| Stage 1 | Motor movement test |
| Stage 2 | Flame sensor testing |
| Stage 3 | Relay and water pump control |
| Stage 4 | Ultrasonic obstacle avoidance |
| Stage 5 | Fire chasing logic |
| Stage 6 | Fire and sonar integration |
| Final Stage | Full autonomous firefighting robot |

---

# How to Upload and Run

## Requirements

- Arduino IDE
- USB Type-A to Type-B cable
- Arduino UNO board

## Upload Steps

1. Install Arduino IDE
2. Open the desired `.ino` sketch
3. Select:
   - Tools → Board → Arduino UNO
4. Select:
   - Tools → Port → Appropriate COM Port
5. Click Upload
6. Open Serial Monitor for debugging output

---

# Safety Notes

- Use only small controlled flames for testing.
- Keep a real fire extinguisher nearby.
- Do not test near flammable materials.
- Disconnect batteries before modifying wiring.
- Do not spray water on electrical fires.

---

# Troubleshooting

| Problem | Possible Cause | Solution |
|---|---|---|
| Motors do not spin | No motor power | Check 12V battery |
| Robot spins incorrectly | Motor polarity reversed | Swap motor wires |
| Flame sensor always LOW | Sensor sensitivity too high | Adjust potentiometer |
| Pump not working | Relay wiring incorrect | Verify relay pin |
| Ultrasonic distance reads zero | TRIG/ECHO swapped | Check wiring |
| Upload fails | Wrong COM port | Reconnect Arduino |

---

# Common Beginner Mistakes

- Forgetting shared GND connections
- Connecting motors directly to Arduino pins
- Reversing ultrasonic TRIG and ECHO pins
- Using weak batteries
- Testing sensors in bright sunlight
- Forgetting to enable motor driver ENA/ENB pins

---

# Mechanical Design

Add your CAD drawings or robot blueprint images here.

```md
images/diagrams/firebot_blueprint.png
```

## Dimensions

| Part | Size |
|---|---|
| Chassis Length | 155.97 mm |
| Chassis Width | 80.00 mm |
| Height | 30.00 mm |
| Wheel Diameter | 61.20 mm |
| Pump Diameter | 60.00 mm |

---

# Future Improvements

Possible upgrades for future versions:

- Wi-Fi or Bluetooth control
- Mobile app integration
- ESP32 based control system
- Camera-based fire detection
- Servo-controlled water nozzle
- Rechargeable battery management
- Mapping and autonomous navigation
- Smoke sensor integration

---


Arduino Robotics Project — Autonomous Firefighting Robot System.

Add video to it 
The ideo named Project_video in assist 
