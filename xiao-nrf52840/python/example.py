# CircuitPython blink example that toggles the on-board red LED (active LOW) every 250 ms.
#
# Buy this module: https://shillehtek.com/products/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable-manual
# More examples: https://github.com/shillehtek/examples
#

# XIAO nRF52840 - CircuitPython Hello World
# Flash the official Adafruit CircuitPython UF2 for "Seeed XIAO nRF52840"
# (or "Seeed XIAO nRF52840 Sense" if you have the Sense version),
# then drop this as code.py on the CIRCUITPY drive.

import board
import digitalio
import time

red = digitalio.DigitalInOut(board.LED_RED)
red.direction = digitalio.Direction.OUTPUT

while True:
    red.value = False   # Active LOW: False = on
    time.sleep(0.25)
    red.value = True    # off
    time.sleep(0.25)
