# Proximity Sensor with Buzzer, LED, and OLED Display

This Arduino project utilizes an ultrasonic proximity sensor to measure the distance to an object. It features an OLED display that shows the measured distance in centimeters and includes a visual progress bar to represent the distance graphically.
Features:

Ultrasonic Proximity Sensor: Measures the distance to the nearest object.
Buzzer: Emits tones that increase in frequency as the object approaches.
LED Indicator: Blinks and changes behavior based on the proximity of the detected object.
OLED Display: Shows the current distance and a progress bar indicating the distance in a user-friendly format.

Components Used:

- Arduino board
- HC-SR04 Ultrasonic Sensor
- Buzzer
- Red LED
- SSD1306 OLED Display
- Connecting wires

How It Works:

The ultrasonic sensor emits a pulse and measures the time it takes for the echo to return.
The distance is calculated based on the time of flight.
The OLED display shows the distance and a progress bar.
The buzzer and LED respond to proximity levels with different sounds and light patterns.

Installation:

1. Connect the components according to the provided schematic.
2. Install the necessary libraries for the OLED display (Adafruit_SSD1306 and Adafruit_GFX).
3. Upload the code to your Arduino board.
