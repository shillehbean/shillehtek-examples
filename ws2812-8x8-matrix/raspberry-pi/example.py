# Runs a column-sweep animation on an 8x8 WS2812 matrix from a Raspberry Pi using the rpi_ws281x library (GPIO 18).
#
# Buy this module: https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
from rpi_ws281x import PixelStrip, Color

# sudo pip3 install rpi_ws281x   |   run with: sudo python3 matrix_demo.py

strip = PixelStrip(64, 18, brightness=40)  # 64 px, GPIO 18
strip.begin()

def xy(x, y, serpentine=False):
    if serpentine and y % 2 == 1:
        return y * 8 + (7 - x)
    return y * 8 + x

while True:
    # column sweep
    for x in range(8):
        for y in range(8):
            strip.setPixelColor(xy(x, y), Color(0, 80, 160))
        strip.show()
        time.sleep(0.08)
    for i in range(64):
        strip.setPixelColor(i, Color(0, 0, 0))
    strip.show()
    time.sleep(0.3)
