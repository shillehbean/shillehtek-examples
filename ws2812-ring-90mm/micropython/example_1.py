# MicroPython script for ESP32 that controls the 24-LED ring with a global brightness cap and provides comet, rainbow, and clock-sweep animation functions.
#
# Buy this module: https://shillehtek.com/products/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# WS2812 24-LED Ring - ESP32 MicroPython Example
# DI->GPIO 13 via 330 ohm, 5V->VIN, GND->GND

from machine import Pin
import neopixel, time

NUM = 24
ring = neopixel.NeoPixel(Pin(13), NUM)
BRIGHT = 0.25                      # global brightness cap

def scale(c):
    return tuple(int(x * BRIGHT) for x in c)

def wheel(pos):
    pos %= 256
    if pos < 85:  return (255 - pos * 3, pos * 3, 0)
    if pos < 170: pos -= 85; return (0, 255 - pos * 3, pos * 3)
    pos -= 170;   return (pos * 3, 0, 255 - pos * 3)

def comet(color, loops=3):
    for t in range(loops * NUM):
        ring.fill((0, 0, 0))
        for tail in range(6):
            i = (t - tail) % NUM
            fade = 1 / (tail + 1)
            ring[i] = scale(tuple(int(x * fade) for x in color))
        ring.write()
        time.sleep_ms(40)

def rainbow(loops=2):
    for j in range(256 * loops):
        for i in range(NUM):
            ring[i] = scale(wheel(i * 256 // NUM + j))
        ring.write()
        time.sleep_ms(10)

def clock_sweep(loops=2):
    for t in range(loops * NUM):
        ring.fill((0, 0, 0))
        ring[t % NUM] = scale((255, 40, 0))
        ring[0] = scale((40, 40, 40))
        ring.write()
        time.sleep_ms(120)

while True:
    comet((0, 120, 255))
    rainbow()
    clock_sweep()
