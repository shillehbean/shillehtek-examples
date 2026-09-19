# MicroPython example that initializes the GC9A01 over SPI, plots concentric colored rings pixel-by-pixel, and writes 'PICO' text.
#
# Buy this module: https://shillehtek.com/products/round-1-28in-ips-lcd-gc9a01-240x240-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/round-1-28in-ips-lcd-gc9a01-240x240-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, SPI
import gc9a01py as gc9a01   # copy gc9a01py.py driver to the board

spi = SPI(1, baudrate=40000000, sck=Pin(10), mosi=Pin(11))
tft = gc9a01.GC9A01(spi,
                    dc=Pin(8, Pin.OUT),
                    cs=Pin(9, Pin.OUT),
                    reset=Pin(12, Pin.OUT),
                    backlight=Pin(13, Pin.OUT),
                    rotation=0)

tft.fill(gc9a01.BLACK)
# concentric gauge rings
for r, color in ((118, gc9a01.CYAN), (90, gc9a01.BLUE), (60, gc9a01.MAGENTA)):
    for a in range(0, 360, 3):
        import math
        x = 120 + int(math.cos(math.radians(a)) * r)
        y = 120 + int(math.sin(math.radians(a)) * r)
        tft.pixel(x, y, color)
tft.text(gc9a01.WHITE, "PICO", 96, 112)
