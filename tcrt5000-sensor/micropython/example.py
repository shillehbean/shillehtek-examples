# MicroPython script for a Raspberry Pi Pico that reads AO via ADC and DO as a digital input, then prints the raw ADC value and whether a line is detected in a loop.
#
# Buy this module: https://shillehtek.com/products/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot-manual
# More examples: https://github.com/shillehtek/examples
#

# TCRT5000 on Raspberry Pi Pico (MicroPython)
# AO -> GP26 (ADC0); DO -> GP15

from machine import ADC, Pin
import time

ao = ADC(26)
do = Pin(15, Pin.IN)

while True:
    raw = ao.read_u16()             # 0 - 65535
    line = do.value() == 0          # LOW = line detected
    print("Raw={:5d}  Line={}".format(raw, "YES" if line else "no"))
    time.sleep(0.1)
