# Raspberry Pi Python example using rpi_ws281x to drive the 24-LED ring on GPIO18, including comet and rainbow animations and a wheel color helper.
#
# Buy this module: https://shillehtek.com/products/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# WS2812 24-LED Ring - Raspberry Pi Example (rpi_ws281x)
# DI->GPIO18 (pin 12) via 330 ohm; run with: sudo python3 ring24_rpi.py
# Install: sudo pip3 install rpi_ws281x  (and disable onboard audio)

import time
from rpi_ws281x import PixelStrip, Color

NUM = 24
strip = PixelStrip(NUM, 18, brightness=60)   # GPIO 18, brightness 0-255
strip.begin()

def comet(color, loops=3):
    for t in range(loops * NUM):
        for i in range(NUM):
            strip.setPixelColor(i, 0)
        for tail in range(6):
            i = (t - tail) % NUM
            fade = 255 // (tail + 1)
            r = ((color >> 16) & 0xFF) * fade // 255
            g = ((color >> 8) & 0xFF) * fade // 255
            b = (color & 0xFF) * fade // 255
            strip.setPixelColor(i, Color(r, g, b))
        strip.show()
        time.sleep(0.04)

def wheel(pos):
    pos %= 256
    if pos < 85:  return Color(255 - pos * 3, pos * 3, 0)
    if pos < 170: pos -= 85; return Color(0, 255 - pos * 3, pos * 3)
    pos -= 170;   return Color(pos * 3, 0, 255 - pos * 3)

def rainbow(loops=2):
    for j in range(256 * loops):
        for i in range(NUM):
            strip.setPixelColor(i, wheel(i * 256 // NUM + j))
        strip.show()
        time.sleep(0.01)

try:
    while True:
        comet(0x0078FF)
        rainbow()
except KeyboardInterrupt:
    for i in range(NUM):
        strip.setPixelColor(i, 0)
    strip.show()
    print("Stopped by user")
