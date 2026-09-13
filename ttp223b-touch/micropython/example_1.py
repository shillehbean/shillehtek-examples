# Monitors the TTP223 input on GPIO4 (ESP32) and prints 'Touched' or 'Released' when the input state changes.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/digital-sensor-ttp223b-module-capacitive-touch-switch-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TTP223B Capacitive Touch Switch - ESP32 MicroPython Example
# Prints "Touched" while the pad is being touched.
# SIG: GPIO 4

from machine import Pin
import time

touch = Pin(4, Pin.IN)

print("TTP223B ready. Touch the pad...")

last = 0
while True:
    val = touch.value()
    if val != last:
        if val == 1:
            print("Touched")
        else:
            print("Released")
        last = val
    time.sleep_ms(20)
