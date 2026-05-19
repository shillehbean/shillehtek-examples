# Blink the onboard LED using CircuitPython (board and digitalio) with a 0.5 second on/off interval.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2-usb-c-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2-usb-c-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# Raspberry Pi Pico 2 - CircuitPython Blink Example
# Flash the latest CircuitPython .uf2 first, then save this as code.py

import board
import digitalio
import time

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

while True:
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)
