# Runs on MicroPython to cycle the on-board WS2812 RGB LED (connected to GP16) through a set of colors.
#
# Buy this module: https://shillehtek.com/products/rp2040-zero-microcontroller-board-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rp2040-zero-microcontroller-board-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# RP2040-Zero - color the on-board WS2812 RGB LED (GP16)
# Flash MicroPython for RP2040 from micropython.org, then save this as main.py

from machine import Pin
from neopixel import NeoPixel
import time

pixel = NeoPixel(Pin(16), 1)

colors = [(64, 0, 0), (0, 64, 0), (0, 0, 64), (32, 32, 32)]
while True:
    for c in colors:
        pixel[0] = c
        pixel.write()
        time.sleep(0.5)
