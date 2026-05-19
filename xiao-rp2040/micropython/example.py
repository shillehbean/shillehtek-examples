# MicroPython example that toggles the user green LED on GP25 every 0.5 seconds (simple blink).
#
# Buy this module: https://shillehtek.com/products/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable-manual
# More examples: https://github.com/shillehtek/examples
#

# XIAO RP2040 - MicroPython Blink
# Flash the official MicroPython RP2040 UF2 firmware first.

from machine import Pin
import time

led = Pin(25, Pin.OUT)   # green LED on GP25 (also serves as user LED)

while True:
    led.toggle()
    time.sleep(0.5)
