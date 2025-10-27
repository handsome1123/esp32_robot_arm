# esp32_robot_arm
esp32-servo-controlled by mobile hotspot

1. Hardware Needed

ESP32 board

Servo motors (1–6, depending on robot arm joints)

Power supply for servos (usually 5–6V; don’t power servos from ESP32 directly)

Jumper wires, breadboard, or proper connectors

---install this library ----
#include <WiFi.h>
#include <ESP32Servo.h>

in this projct, it applied AJAX for real time movement 

int this step, there are only 2 sliders (base + elbow) 
I use my mobilbe passwad 
but make sure to see in conroll intface, use same network - hospost 
**don't need internet bill to do this projejct **


Wiring -----

base servo motor - ESP32 pin 26
shoulder servo motor - ESP32 pin 27

Servo 
brown color -v supply ----------- ESP32 Vin/5V
red color +v supply ------------- ESP32 GND

make sure to replace your hotpost 
SSID= replace with your wifi
password = repace with your hotpost password 
