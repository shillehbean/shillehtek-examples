# ESP32 MicroPython script that pulses the JSN-SR04T trigger, measures echo pulse duration with time_pulse_us, returns median distance in cm, and prints distance or status messages including blind-zone and out-of-range handling.
#
# Buy this module: https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# JSN-SR04T - ESP32 MicroPython Example
# Trig->GPIO 5, Echo->GPIO 18 (via 1k/2k divider), 5V->VIN

from machine import Pin, time_pulse_us
import time

trig = Pin(5, Pin.OUT, value=0)
echo = Pin(18, Pin.IN)

def read_once_cm():
    trig.value(0); time.sleep_us(4)
    trig.value(1); time.sleep_us(10)
    trig.value(0)
    us = time_pulse_us(echo, 1, 40000)   # 40 ms timeout
    return -1 if us < 0 else us // 58

def read_median_cm():
    vals = []
    for _ in range(3):
        vals.append(read_once_cm())
        time.sleep_ms(60)
    return sorted(vals)[1]

print("JSN-SR04T ready (blind zone < ~25 cm)")
while True:
    cm = read_median_cm()
    if cm < 0:
        print("Out of range / no echo")
    elif cm < 25:
        print("Too close (blind zone)")
    else:
        print("Distance: {} cm".format(cm))
    time.sleep(0.3)
