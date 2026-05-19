# Blink the onboard LED on the Pico 2W using MicroPython, using the 'LED' alias routed through the CYW43 wireless chip.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2w-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# Raspberry Pi Pico 2W - MicroPython Blink Example
# The onboard LED on the 2W is routed through the CYW43 wireless chip,
# so we use the "LED" alias instead of GP25.

from machine import Pin
import time

led = Pin("LED", Pin.OUT)

while True:
    led.value(1)
    time.sleep(0.5)
    led.value(0)
    time.sleep(0.5)
