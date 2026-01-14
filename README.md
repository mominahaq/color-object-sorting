Automated Object Sorting System

Material- and Color-Based Robotic Sorting Using Sensor Fusion

Overview

This project implements an automated conveyor-based object sorting system using embedded control and multiple sensors. Objects are detected, classified by material (metal / non-metal) and color (red / blue), and then directed into appropriate bins using servo actuators. The system demonstrates real-time decision-making, sensor fusion, and deterministic control logic commonly used in industrial robotics and automation.

System Architecture

The system is centered around a microcontroller that coordinates sensing, decision-making, and actuation. A DC motor-driven conveyor transports objects through a sensing zone, where multiple sensors collect data. Based on this data, the controller activates one of four servo-driven sorting mechanisms.

Sorting Categories :

Metal + Red

Metal + Blue

Non-Metal + Red

Non-Metal + Blue

Hardware Components:

IR Sensor – Detects the presence of an object on the conveyor

Inductive Proximity Sensor – Identifies metallic objects

TCS3200 Color Sensor – Measures RGB color intensities

L298N Motor Driver – Controls conveyor motor speed and direction

DC Motor – Drives the conveyor belt

4 Servo Motors – Actuate sorting gates for each category

Microcontroller (Arduino-compatible)

Working Principle:

Objects move along the conveyor belt.
An IR sensor detects when an object reaches the sensing zone.
The conveyor is temporarily stopped to ensure accurate sensing.
The inductive sensor determines whether the object is metallic.
The color sensor measures red, green, and blue intensity values.
The controller applies sorting logic to classify the object.
The corresponding servo motor is actuated to redirect the object.
Servos return to the home position and the conveyor resumes operation.

Control Logic:

The sorting decision is based on two binary conditions:

Material: Metal or Non-Metal

Color: Red or Blue

The system uses a rule-based logic structure to map these conditions to one of four outputs. This approach ensures predictable and repeatable behavior, which is essential for real-time robotic systems.

Software Implementation

Written in Arduino C++

Modular structure with dedicated functions for:

Color sensing

Conveyor control

Servo reset

Uses pulse-width measurement from the TCS3200 for color detection

Includes serial output for debugging and system monitoring

Key Features:

Real-time object detection and classification

Sensor fusion using material and color data

Deterministic sorting logic with no ambiguity

Modular and scalable design

Clear separation of sensing, logic, and actuation

Applications:

Industrial automation and material handling
Smart recycling and waste segregation
Robotics education and laboratory demonstrations
Mechatronics and embedded systems projects

Future Improvements:

Add weight-based classification using load cells
Implement PID speed control for the conveyor
Introduce camera-based vision for advanced color detection
Replace rule-based logic with machine learning classifiers
Add data logging and performance metrics

Skills Demonstrated:

Embedded systems programming

Sensor integration and calibration

Actuator control (DC motors and servos)

Real-time control logic

Robotics system design
