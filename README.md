# IoT-based Smart Cultivation Monitoring and Management System

My university project demonstrating a comprehensive IoT system to monitor and automate plant care.

## 📸 Project Showcase

Below are images of the final hardware prototype and the Blynk mobile dashboard.

### Hardware
The completed circuit includes the ESP32, sensors, 16x2 LCD, relay, and pump, all mounted on a prototype board.


<img width="401" height="535" alt="image" src="https://github.com/user-attachments/assets/eaeec1ac-1484-422a-ae91-53a2cb2d5973" />


### Blynk Dashboard
A custom dashboard built in the Blynk app for remote monitoring and control. The app displays real-time data and includes controls for the water pump and automation mode.


<img width="329" height="706" alt="image" src="https://github.com/user-attachments/assets/49e2af6a-4a99-4fbe-89d7-96fb986208b0" />

### Web Dashboard
A custom-built web dashboard using HTML, CSS, and JavaScript (Chart.js) to visualize all real-time sensor data and historical trends in a user-friendly interface.
<img width="1251" height="808" alt="image" src="https://github.com/user-attachments/assets/54f679f3-7022-459e-8883-dbf348c27f16" />

## Core Functions

* **Data Acquisition:** Integrated sensors (Soil Moisture, DHT11 Temperature & Humidity, Light) to track environmental conditions in real-time.
* **Local Display:** Utilized a 16x2 LCD screen to provide immediate, on-site feedback of all parameters and system status (as seen in the hardware photo).
* **Remote Monitoring & Control:** Built the mobile dashboard (shown above) using the **Blynk** platform, enabling users to monitor data remotely and manually control the water pump.
* **Automation:** Programmed an automated irrigation logic that activates a water pump (via Relay) based on preset soil moisture thresholds (e.g., ON <30%, OFF >60%).

## 🛠️ Technologies Used

* **Microcontroller:** ESP32
* **IoT Platform:** Blynk (Blynk App, Blynk Server)
* **Hardware:** Soil Moisture Sensor, DHT11 Sensor, 16x2 I2C LCD, Relay Module, Water Pump
* **Language:** C++ (Arduino)

## 💻 Project Code
    
The main code for the ESP32 is included in the `SmartFarm.ino` (or `main.cpp`) file.
