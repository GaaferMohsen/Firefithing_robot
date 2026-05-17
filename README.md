# Autonomous Firefighting Robot

A beginner-friendly autonomous robot that detects fire using flame sensors and extinguishes it with a water pump, powered by an Arduino UNO.

---

# Table of Contents

1. Project Overview  
2. Features  
3. Project Demo Video  
4. Components List  
5. How It Works  
6. Circuit Diagram  
7. Folder Structure  
8. Pin Connections  
9. PID Control Explanation  
10. Code Development Stages  
11. How to Upload and Run  
12. Safety Notes  
13. Troubleshooting  
14. Mechanical Design  
15. Future Improvements  
16. License  
17. Author  

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

---

# Features

- Autonomous fire detection  
- Automatic fire extinguishing  
- Obstacle avoidance  
- Multi-direction flame sensing  
- Arduino UNO based control system  
- Relay-controlled water pump  

---

# Project Demo Video

[Watch Project Video](./Project_video.mp4)

---

# Components List

Arduino UNO, L298N Motor Driver, DC Motors, Flame Sensors, HC-SR04, Relay Module, Water Pump, Batteries, etc.

---

# How It Works

Robot searches → detects fire → moves toward it → avoids obstacles → activates pump → resumes search.

---

# PID Control Example

float Kp = 1.5;
float Kd = 0.5;

error = left - right;
correction = Kp*error + Kd*(error-lastError);

---

# Folder Structure

Firefighting_Robot/
- code/
- docs/
- images/
- hardware/

---

# Safety Notes

Use small flames only. Keep extinguisher nearby.

---

# Author

Your Name Here
