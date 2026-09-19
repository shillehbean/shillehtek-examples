# ESP32 MicroPython script that reads the SW-520D on GPIO27 with debounce and prints the tilt state to the REPL.
#
# Buy this module: https://shillehtek.com/products/tilt-switch-sw-520d-vibration-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tilt-switch-sw-520d-vibration-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# SW-520D Tilt Switch Module - ESP32 MicroPython Example
# D0->GPIO 27, VCC->3V3, GND->GND

from machine import Pin
import time

tilt = Pin(27, Pin.IN)

DEBOUNCE_MS = 60
stable = tilt.value()
last_reading = stable
last_change = time.ticks_ms()

print("Tilt sensor ready - tip me over!")
while True:
    reading = tilt.value()

    if reading != last_reading:
        last_change = time.ticks_ms()
        last_reading = reading

    if (time.ticks_diff(time.ticks_ms(), last_change) > DEBOUNCE_MS
            and reading != stable):
        stable = reading
        print("TILTED!" if stable else "Level again")

    time.sleep_ms(5)
