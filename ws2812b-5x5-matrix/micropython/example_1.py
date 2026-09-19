# MicroPython script for ESP32 that maps a 5x5 WS2812B matrix, applies brightness scaling, draws heart and smile bitmaps, and runs a bouncing-pixel animation.
#
# Buy this module: https://shillehtek.com/products/ws2812b-5x5-rgb-led-matrix-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812b-5x5-rgb-led-matrix-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# WS2812B 5x5 Matrix - ESP32 MicroPython Example
# DIN->GPIO 13 via 330 ohm, VCC->VIN(5V), GND->GND

from machine import Pin
import neopixel, time

W = H = 5
SERPENTINE = False
px = neopixel.NeoPixel(Pin(13), W * H)
BRIGHT = 0.2

def xy(x, y):
    if SERPENTINE and y % 2 == 1:
        return y * W + (W - 1 - x)
    return y * W + x

def scale(c):
    return tuple(int(v * BRIGHT) for v in c)

HEART = [0b01010, 0b11111, 0b11111, 0b01110, 0b00100]
SMILE = [0b01010, 0b01010, 0b00000, 0b10001, 0b01110]

def draw(bitmap, color):
    px.fill((0, 0, 0))
    for y in range(H):
        for x in range(W):
            if bitmap[y] & (1 << (W - 1 - x)):
                px[xy(x, y)] = scale(color)
    px.write()

def bounce(loops=3):
    x, y, dx, dy = 0, 0, 1, 1
    for _ in range(loops * 20):
        px.fill((0, 0, 0))
        px[xy(x, y)] = scale((0, 255, 120))
        px.write()
        x += dx; y += dy
        if x in (0, W - 1): dx = -dx
        if y in (0, H - 1): dy = -dy
        time.sleep_ms(100)

while True:
    draw(HEART, (255, 0, 40));  time.sleep(0.6)
    draw(SMILE, (255, 160, 0)); time.sleep(0.6)
    bounce()
