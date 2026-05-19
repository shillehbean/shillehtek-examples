# Runs on a Raspberry Pi Pico under MicroPython to read the MQ-2 analog input (with a 2:1 divider) and digital alarm pin, compute the real sensor voltage, and print raw readings and alarm status in a loop.
#
# Buy this module: https://shillehtek.com/products/mq-2-flammable-gas-smoke-sensor-module-for-arduino-safety
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-2-flammable-gas-smoke-sensor-module-for-arduino-safety-manual
# More examples: https://github.com/shillehtek/examples
#

# MQ-2 on Raspberry Pi Pico (MicroPython)
# AO -> 2:1 divider -> GP26 (ADC0); DO -> GP15

from machine import ADC, Pin
import time

ao = ADC(26)
do = Pin(15, Pin.IN)

print("Warming up MQ-2 - wait 1-3 minutes for stable values")

while True:
    raw = ao.read_u16()
    v_pin  = raw * 3.3 / 65535
    v_real = v_pin * 2
    alarm  = " ALARM" if do.value() == 0 else ""
    print("Raw={:5d}  Vreal={:.2f} V{}".format(raw, v_real, alarm))
    time.sleep(0.5)
