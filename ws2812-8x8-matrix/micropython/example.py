# Displays an expanding orange square animation on an 8x8 WS2812 matrix under MicroPython using the neopixel module with optional serpentine mapping and brightness scaling.
#
# Buy this module: https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
from neopixel import NeoPixel
import time

np = NeoPixel(Pin(0), 64)
BRIGHT = 0.1   # 10%

def xy(x, y, serpentine=False):
    if serpentine and y % 2 == 1:
        return y * 8 + (7 - x)
    return y * 8 + x

def put(x, y, r, g, b):
    np[xy(x, y)] = (int(r * BRIGHT), int(g * BRIGHT), int(b * BRIGHT))

while True:
    # expanding square
    for ring in range(4):
        lo, hi = 3 - ring, 4 + ring
        for x in range(lo, hi + 1):
            put(x, lo, 255, 60, 0)
            put(x, hi, 255, 60, 0)
        for y in range(lo, hi + 1):
            put(lo, y, 255, 60, 0)
            put(hi, y, 255, 60, 0)
        np.write()
        time.sleep(0.15)
    time.sleep(0.3)
    np.fill((0, 0, 0))
    np.write()
