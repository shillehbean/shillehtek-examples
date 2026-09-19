# MicroPython script for the Raspberry Pi Pico that reads the SW-520D on GP16 with debounce, mirrors the tilt state to the onboard LED, and prints status messages.
#
# Buy this module: https://shillehtek.com/products/tilt-switch-sw-520d-vibration-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tilt-switch-sw-520d-vibration-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# SW-520D Tilt Switch Module - Pico MicroPython Example
# D0->GP16, VCC->3V3(OUT), GND->GND
# Onboard LED mirrors the tilt state.

from machine import Pin
import time

tilt = Pin(16, Pin.IN)
led = Pin("LED", Pin.OUT)

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
        led.value(stable)
        print("TILTED!" if stable else "Level again")

    time.sleep_ms(5)
