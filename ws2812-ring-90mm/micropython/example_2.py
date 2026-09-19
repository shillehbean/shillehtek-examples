# MicroPython example for the Raspberry Pi Pico that implements spinner and breathe animations on the 24-LED ring connected to GP0 and runs them in a loop.
#
# Buy this module: https://shillehtek.com/products/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# WS2812 24-LED Ring - Pico MicroPython Example
# DI->GP0 via 330 ohm, 5V->VBUS, GND->GND

from machine import Pin
import neopixel, time

NUM = 24
ring = neopixel.NeoPixel(Pin(0), NUM)
BRIGHT = 0.25

def scale(c):
    return tuple(int(x * BRIGHT) for x in c)

def breathe(color, cycles=3):
    for _ in range(cycles):
        for level in list(range(0, 100)) + list(range(100, 0, -1)):
            ring.fill(tuple(int(x * level / 100 * BRIGHT) for x in color))
            ring.write()
            time.sleep_ms(8)

def spinner(color, loops=4):
    for t in range(loops * NUM):
        ring.fill((0, 0, 0))
        for k in range(3):                      # 3 arms
            ring[(t + k * NUM // 3) % NUM] = scale(color)
        ring.write()
        time.sleep_ms(50)

while True:
    spinner((0, 255, 80))
    breathe((120, 0, 255))
