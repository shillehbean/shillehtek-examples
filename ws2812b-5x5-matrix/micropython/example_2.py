# MicroPython script for the Raspberry Pi Pico that maps a 5x5 WS2812B matrix, scales brightness, displays tiny 5x5 digit bitmaps (0–3), and cycles through them.
#
# Buy this module: https://shillehtek.com/products/ws2812b-5x5-rgb-led-matrix-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812b-5x5-rgb-led-matrix-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# WS2812B 5x5 Matrix - Pico MicroPython Example
# DIN->GP0 via 330 ohm, VCC->VBUS(5V), GND->GND

from machine import Pin
import neopixel, time

W = H = 5
SERPENTINE = False
px = neopixel.NeoPixel(Pin(0), W * H)
BRIGHT = 0.2

def xy(x, y):
    if SERPENTINE and y % 2 == 1:
        return y * W + (W - 1 - x)
    return y * W + x

def scale(c):
    return tuple(int(v * BRIGHT) for v in c)

DIGITS = {                     # tiny 5x5 digits 0-3 (add more!)
    0: [0b01110, 0b10001, 0b10001, 0b10001, 0b01110],
    1: [0b00100, 0b01100, 0b00100, 0b00100, 0b01110],
    2: [0b01110, 0b10001, 0b00110, 0b01000, 0b11111],
    3: [0b11110, 0b00001, 0b00110, 0b00001, 0b11110],
}

def draw(bitmap, color):
    px.fill((0, 0, 0))
    for y in range(H):
        for x in range(W):
            if bitmap[y] & (1 << (W - 1 - x)):
                px[xy(x, y)] = scale(color)
    px.write()

count = 0
while True:
    draw(DIGITS[count % 4], (0, 200, 255))
    count += 1
    time.sleep(1)
