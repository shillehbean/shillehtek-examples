# Runs on a Pico to detect rising touch events from the TTP223 on GP15 and toggle the onboard LED while printing the LED state.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/digital-sensor-ttp223b-module-capacitive-touch-switch-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TTP223B Capacitive Touch Switch - Pico MicroPython Example
# Toggles the onboard LED each time the pad is touched.
# SIG: GP15

from machine import Pin
import time

touch = Pin(15, Pin.IN)
led = Pin("LED", Pin.OUT)

led_state = False
last = 0

print("TTP223B ready. Touch the pad...")

while True:
    val = touch.value()
    # Rising-edge detection
    if val == 1 and last == 0:
        led_state = not led_state
        led.value(1 if led_state else 0)
        print("LED ON" if led_state else "LED OFF")
    last = val
    time.sleep_ms(20)
