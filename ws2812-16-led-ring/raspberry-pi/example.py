# Raspberry Pi Python example using the rpi_ws281x PixelStrip to perform spinner and gauge animations on the WS2812 ring wired to GPIO18.
#
# Buy this module: https://shillehtek.com/products/ws2812-16-led-addressable-rgb-ring
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-16-led-addressable-rgb-ring-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# WS2812 16-LED Ring - Raspberry Pi Example (rpi_ws281x)
# DI->GPIO18 (pin 12) via 330 ohm; run with sudo
# Install: sudo pip3 install rpi_ws281x

import time
from rpi_ws281x import PixelStrip, Color

NUM = 16
strip = PixelStrip(NUM, 18, brightness=60)
strip.begin()

def clear():
    for i in range(NUM):
        strip.setPixelColor(i, 0)

def spinner(color, loops=4):
    for t in range(loops * NUM):
        clear()
        strip.setPixelColor(t % NUM, color)
        strip.setPixelColor((t + 1) % NUM, color)
        strip.show()
        time.sleep(0.06)

def gauge(percent):
    lit = percent * NUM // 100
    clear()
    for i in range(lit):
        r = i * 255 // (NUM - 1)
        g = 255 - r
        strip.setPixelColor(i, Color(r, g, 0))
    strip.show()

try:
    while True:
        spinner(Color(0, 120, 255))
        for p in range(0, 101, 5):
            gauge(p)
            time.sleep(0.08)
        time.sleep(0.6)
except KeyboardInterrupt:
    clear(); strip.show()
    print("Stopped by user")
