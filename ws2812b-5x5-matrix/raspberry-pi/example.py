# Raspberry Pi Python example using rpi_ws281x to control a 5x5 WS2812B matrix, draw a heart bitmap, and perform a column-sweep animation (with serpentine mapping option).
#
# Buy this module: https://shillehtek.com/products/ws2812b-5x5-rgb-led-matrix-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812b-5x5-rgb-led-matrix-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# WS2812B 5x5 Matrix - Raspberry Pi Example (rpi_ws281x)
# DIN->GPIO18 (pin 12) via 330 ohm; run with sudo
# Install: sudo pip3 install rpi_ws281x

import time
from rpi_ws281x import PixelStrip, Color

W = H = 5
SERPENTINE = False
strip = PixelStrip(W * H, 18, brightness=50)
strip.begin()

def xy(x, y):
    if SERPENTINE and y % 2 == 1:
        return y * W + (W - 1 - x)
    return y * W + x

HEART = [0b01010, 0b11111, 0b11111, 0b01110, 0b00100]

def clear():
    for i in range(W * H):
        strip.setPixelColor(i, 0)

def draw(bitmap, color):
    clear()
    for y in range(H):
        for x in range(W):
            if bitmap[y] & (1 << (W - 1 - x)):
                strip.setPixelColor(xy(x, y), color)
    strip.show()

def column_sweep(color, loops=3):
    for _ in range(loops):
        for x in range(W):
            clear()
            for y in range(H):
                strip.setPixelColor(xy(x, y), color)
            strip.show()
            time.sleep(0.12)

try:
    while True:
        draw(HEART, Color(255, 0, 40))
        time.sleep(0.8)
        column_sweep(Color(0, 120, 255))
except KeyboardInterrupt:
    clear(); strip.show()
    print("Stopped by user")
