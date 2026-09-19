# Raspberry Pi Pico MicroPython countdown-timer demo that empties the ring over a specified number of seconds and then flashes the LEDs (using GP0).
#
# Buy this module: https://shillehtek.com/products/ws2812-16-led-addressable-rgb-ring
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-16-led-addressable-rgb-ring-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# WS2812 16-LED Ring - Pico MicroPython Example
# DI->GP0 via 330 ohm, 5V->VBUS, GND->GND
# Countdown-timer demo: ring empties over N seconds, then flashes.

from machine import Pin
import neopixel, time

NUM = 16
ring = neopixel.NeoPixel(Pin(0), NUM)
BRIGHT = 0.25

def scale(c):
    return tuple(int(v * BRIGHT) for v in c)

def countdown(seconds=16):
    per_led = seconds / NUM
    for lit in range(NUM, 0, -1):
        ring.fill((0, 0, 0))
        for i in range(lit):
            color = (0, 255, 60) if lit > NUM // 4 else (255, 30, 0)
            ring[i] = scale(color)
        ring.write()
        time.sleep(per_led)

def flash(color, times=4):
    for _ in range(times):
        ring.fill(scale(color)); ring.write(); time.sleep_ms(120)
        ring.fill((0, 0, 0));    ring.write(); time.sleep_ms(120)

while True:
    countdown(16)          # 1 LED per second
    flash((255, 0, 0))
    time.sleep(1)
