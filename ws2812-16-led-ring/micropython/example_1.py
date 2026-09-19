# ESP32 MicroPython example using the neopixel module to implement spinner, gauge, and breathing animations on GPIO13 with brightness scaling.
#
# Buy this module: https://shillehtek.com/products/ws2812-16-led-addressable-rgb-ring
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-16-led-addressable-rgb-ring-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# WS2812 16-LED Ring - ESP32 MicroPython Example
# DI->GPIO 13 via 330 ohm, 5V->VIN, GND->GND

from machine import Pin
import neopixel, time

NUM = 16
ring = neopixel.NeoPixel(Pin(13), NUM)
BRIGHT = 0.25

def scale(c):
    return tuple(int(v * BRIGHT) for v in c)

def spinner(color, loops=4):
    for t in range(loops * NUM):
        ring.fill((0, 0, 0))
        ring[t % NUM] = scale(color)
        ring[(t + 1) % NUM] = scale(color)
        ring[(t - 1) % NUM] = scale((10, 10, 30))
        ring.write()
        time.sleep_ms(60)

def gauge(percent):
    lit = percent * NUM // 100
    ring.fill((0, 0, 0))
    for i in range(lit):
        r = i * 255 // (NUM - 1)
        g = 255 - r
        ring[i] = scale((r, g, 0))
    ring.write()

def breathe(color, cycles=2):
    for _ in range(cycles):
        for lv in list(range(0, 100)) + list(range(100, 0, -1)):
            ring.fill(tuple(int(v * lv / 100 * BRIGHT) for v in color))
            ring.write()
            time.sleep_ms(10)

while True:
    spinner((0, 120, 255))
    for p in range(0, 101, 5):
        gauge(p)
        time.sleep_ms(80)
    breathe((150, 0, 255))
