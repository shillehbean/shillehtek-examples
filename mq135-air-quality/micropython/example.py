# Runs on a Raspberry Pi Pico with MicroPython: reads AO via ADC0 (accounting for a 2:1 voltage divider), reads DO on GP15, and prints the raw ADC value, reconstructed sensor voltage, and DO state repeatedly.
#
# Buy this module: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# MQ-135 on Raspberry Pi Pico (MicroPython)
# AO -> 2:1 divider -> GP26 (ADC0); DO -> GP15

from machine import ADC, Pin
import time

ao = ADC(26)
do = Pin(15, Pin.IN)

print("Warming up MQ-135 - wait 1-3 minutes for stable values")

while True:
    raw = ao.read_u16()              # 0 - 65535
    v_pin  = raw * 3.3 / 65535       # voltage at the GPIO
    v_real = v_pin * 2               # un-divide the 2:1 divider
    print("Raw={:5d}  Vreal={:.2f} V  DO={}".format(raw, v_real, do.value()))
    time.sleep(0.5)
