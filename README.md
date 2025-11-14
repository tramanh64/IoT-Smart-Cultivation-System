# IoT-based Smart Cultivation Monitoring and Management System

My university project demonstrating a comprehensive IoT system to monitor and automate plant care.

## Core Functions

* **Data Acquisition:** Integrated sensors (Soil Moisture, DHT11 Temperature & Humidity, Light) to track environmental conditions in real-time.
* **Local Display:** Utilized a 16x2 LCD screen to provide immediate, on-site feedback of all parameters and system status.
* **Remote Monitoring & Control:** Built a mobile dashboard using the **Blynk** platform, enabling users to monitor data remotely and manually control the water pump.
* **Automation:** Programmed an automated irrigation logic that activates a water pump (via Relay) based on preset soil moisture thresholds (e.g., ON <30%, OFF >60%).

## Technologies Used

* **Microcontroller:** ESP32
* **IoT Platform:** Blynk (Blynk App, Blynk Server)
* **Hardware:** Soil Moisture Sensor, DHT11 Sensor, 16x2 I2C LCD, Relay Module
* **Language:** C++ (Arduino)

## Project Code

The main code for the ESP32 is included in the `SmartFarm.ino` (hoặc tên file code của bạn) file.