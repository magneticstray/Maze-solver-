[# Maze-solver
IR Proximity Sensor Calibration & Usage Guide

This project provides a two-step process for accurately measuring distance using a simple IR (Infrared) LED and photodiode pair. It includes a dedicated calibration sketch to find sensor-specific constants and a main sketch for real-world distance measurement.

The primary goal of the calibration is to create a mathematical model that compensates for ambient light and the non-linear response of the sensor, resulting in more reliable readings.

Hardware Required

An Arduino-compatible microcontroller (e.g., NodeMCU, Wemos D1 Mini, Arduino Uno).

An IR Emitter LED (the clear one).

An IR Receiver/Photodiode (the black one).

A breadboard and jumper wires.

A flat, white object to use as a calibration target (e.g., a piece of cardstock or a small box).

A ruler or measuring tape.

How It Works

The amount of IR light from the emitter that reflects off an object and hits the receiver is used to estimate distance. However, this relationship is not linear and is heavily affected by ambient light in the room.

This system tackles the problem in two stages:

Ambient Light Cancellation: The calibration code first measures the sensor's reading without the IR emitter's light. This "ambient offset" is then subtracted from all future readings to isolate the signal from the reflected IR light.

Curve Fitting: The relationship between the corrected sensor reading and the actual distance is not linear. It often follows an inverse relationship. The calibration sketch measures the sensor's response at several known distances and then uses linear regression to fit the data to an equation of the form:
distance = K / (sensorValue - C)
Where K and C are the unique calibration constants for your sensor and environment.

Wiring

Connect the components as follows. Note that the IR receiver is an analog sensor.

IR Emitter LED:

Anode (longer leg) to pin D1 on the microcontroller.

Cathode (shorter leg) to GND.

IR Receiver Photodiode:

Signal pin to A0 on the microcontroller.

VCC/+ pin to 3.3V or 5V.

GND pin to GND.

Step 1: The Calibration Process

This is the most critical step. Accurate calibration will lead to accurate measurements.

Upload the Calibration Sketch: Open the first code file (calibration_sketch.ino) in the Arduino IDE and upload it to your microcontroller.

Open Serial Monitor: Open the Serial Monitor and set the baud rate to 115200.

Calibrate Ambient Light:

You will see the first prompt: --- STAGE 1: Ambient Light Calibration ---.

As instructed, completely cover the clear IR Emitter LED with your finger or tape. Do not cover the black receiver.

Type c into the Serial Monitor input box and press Enter.

The device will take a few readings and calculate the ambientOffset.

Calibrate Distances:

Uncover the IR Emitter LED.

You will now see prompts for --- STAGE 2: Distance Calibration ---.

Using your ruler, place the flat, white object at the first prompted distance (e.g., 3 cm) directly in front of the sensor pair.

Press Enter in the Serial Monitor. The device will record the corrected sensor value for that distance.

Repeat this process for all the distances prompted by the sketch (3, 5, 7, 10, 15, 20 cm). Be as precise as possible with your measurements.

Get Your Constants:

After the final distance is measured, the sketch will perform the curve fitting calculations.

It will output your unique K and C values. Write these two numbers down!

--- Curve Fit Results ---
Your new calibration constants are:
K = -526.13
C = 329.46


Step 2: Using the Main Sketch

Now you can use your calibration constants to get real-time distance measurements.

Update the Main Sketch: Open the second code file (main_robot_sketch.ino).

Enter Your Constants: Find these two lines at the top of the code:

const float K = -526.13;
const float C = 329.46;


Replace the example values with the K and C values you wrote down from the calibration step.

Upload and Run: Upload the modified sketch to your microcontroller.

View Results: Open the Serial Monitor (baud 115200). The device will now continuously print the calculated distance of any object in front of it.

Important Notes

Recalibration is Key: The K and C values are highly dependent on the ambient lighting conditions of the room. If you move the sensor to a different room or if the lighting changes significantly (e.g., from day to night), you should run the calibration sketch again to get new, more accurate constants.

Reliable Range: This type of sensor is most reliable for short distances. The example code includes a check to only print distances between 2 cm and 10 cm. You may need to adjust this range based on your sensor's performance.

Object Surface: The calibration was designed using a white, non-glossy surface. Dark, transparent, or highly reflective objects will give different readings and may not be measured accurately.
](https://gemini.google.com/share/1a9c5104729c)
