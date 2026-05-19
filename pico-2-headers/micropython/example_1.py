# Blink the onboard LED on GP25 using MicroPython with a 0.5 second on/off interval.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2-usb-c-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2-usb-c-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# Raspberry Pi Pico 2 - MicroPython Blink Example
# Blinks the onboard LED on GP25

from machine import Pin
import time

led = Pin(25, Pin.OUT)

while True:
    led.value(1)
    time.sleep(0.5)
    led.value(0)
    time.sleep(0.5)
