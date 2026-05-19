# MicroPython script for Raspberry Pi Pico that reads raw RGB pulse widths from the TCS3200 using time_pulse_us and prints the values (20% frequency scaling).
#
# Buy this module: https://shillehtek.com/products/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects-manual
# More examples: https://github.com/shillehtek/examples
#

# GY-31 TCS3200 on Raspberry Pi Pico (MicroPython)
# Wiring: S0=GP10 S1=GP11 S2=GP12 S3=GP13 OUT=GP14

from machine import Pin, time_pulse_us
import time

S0 = Pin(10, Pin.OUT); S1 = Pin(11, Pin.OUT)
S2 = Pin(12, Pin.OUT); S3 = Pin(13, Pin.OUT)
OUT = Pin(14, Pin.IN)

# 20% frequency scaling
S0.value(1); S1.value(0)

def read(s2, s3):
    S2.value(s2); S3.value(s3)
    time.sleep_ms(50)
    return time_pulse_us(OUT, 0, 30000)  # microseconds per low half-cycle

while True:
    r = read(0, 0)
    b = read(0, 1)
    g = read(1, 1)
    print("R={:4d}  G={:4d}  B={:4d}".format(r, g, b))
    time.sleep(0.3)
