# MicroPython example for an ESP32 that reads a reed switch on GPIO25 with pull-up, debounces the input, and prints OPEN/CLOSED state changes to the REPL.
#
# Buy this module: https://shillehtek.com/products/reed-switch-magnetic-sensor-normally-open-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/reed-switch-magnetic-sensor-normally-open-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Reed Switch Door Monitor - ESP32 MicroPython Example
# Lead 1 -> GPIO 25, Lead 2 -> GND

from machine import Pin
import time

reed = Pin(25, Pin.IN, Pin.PULL_UP)   # 1 = open, 0 = magnet present
last = reed.value()

print("Monitoring door...")

while True:
    state = reed.value()
    if state != last:
        time.sleep_ms(30)             # debounce
        state = reed.value()
        if state != last:
            if state == 0:
                print("CLOSED - magnet present")
            else:
                print("OPEN - magnet away!")
            last = state
    time.sleep_ms(10)
