# Raspberry Pi Pico MicroPython water-tank demo that measures distance from the JSN-SR04T, computes water depth and percent-full based on tank depth and sensor offset, and prints air gap/water/tank percentage periodically.
#
# Buy this module: https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# JSN-SR04T - Pico MicroPython Example (water tank level demo)
# Trig->GP3, Echo->GP2 (via 1k/2k divider), 5V->VBUS

from machine import Pin, time_pulse_us
import time

trig = Pin(3, Pin.OUT, value=0)
echo = Pin(2, Pin.IN)

TANK_DEPTH_CM = 120         # sensor face to tank bottom
SENSOR_OFFSET = 25          # keep sensor above max water by blind zone

def read_cm():
    trig.value(1); time.sleep_us(10); trig.value(0)
    us = time_pulse_us(echo, 1, 40000)
    return -1 if us < 0 else us // 58

while True:
    cm = read_cm()
    if cm < 0:
        print("No echo")
    else:
        water = TANK_DEPTH_CM - cm
        pct = max(0, min(100, water * 100 // (TANK_DEPTH_CM - SENSOR_OFFSET)))
        print("Air gap: {} cm | Water: {} cm | Tank: {}%".format(cm, water, pct))
    time.sleep(1)
