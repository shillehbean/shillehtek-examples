# Micropython examples

- [`example_1.py`](./example_1.py) — ESP32 MicroPython script that pulses the JSN-SR04T trigger, measures echo pulse duration with time_pulse_us, returns median distance in cm, and prints distance or status messages including blind-zone and out-of-range handling.
- [`example_2.py`](./example_2.py) — Raspberry Pi Pico MicroPython water-tank demo that measures distance from the JSN-SR04T, computes water depth and percent-full based on tank depth and sensor offset, and prints air gap/water/tank percentage periodically.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32-manual)  
Buy the module: https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
