# CircuitPython example that cycles the on-board NeoPixel through red, green, and blue with a 0.4 second delay between colors.
#
# Buy this module: https://shillehtek.com/products/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable-manual
# More examples: https://github.com/shillehtek/examples
#

# XIAO RP2040 - CircuitPython Hello World
# Flash the official Adafruit CircuitPython UF2 for "Seeed XIAO RP2040",
# then drop this as code.py on the CIRCUITPY drive.

import board
import neopixel
import time

pixel = neopixel.NeoPixel(board.NEOPIXEL, 1, brightness=0.2)

while True:
    pixel[0] = (255, 0, 0)
    time.sleep(0.4)
    pixel[0] = (0, 255, 0)
    time.sleep(0.4)
    pixel[0] = (0, 0, 255)
    time.sleep(0.4)
