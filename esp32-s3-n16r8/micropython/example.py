# Displays free heap in MicroPython and cycles the onboard WS2812 RGB LED on GPIO48; this does not independently verify PSRAM support.
#
# Buy this module: https://shillehtek.com/products/esp32-s3-n16r8-development-board-pre-soldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-n16r8-development-board-pre-soldered-headers-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ESP32-S3 N16R8 board check in MicroPython - show free memory, cycle the RGB LED
# RGB LED = GPIO 48 (WS2812). Flash the ESP32-S3 firmware with Octal-SPIRAM support
# to use the 8 MB PSRAM.
from machine import Pin
from neopixel import NeoPixel
import gc
import time

led = NeoPixel(Pin(48), 1)
print("Free memory (bytes):", gc.mem_free())

colors = [(32, 0, 0), (0, 32, 0), (0, 0, 32), (0, 0, 0)]    # red, green, blue, off
while True:
    for color in colors:
        led[0] = color
        led.write()
        time.sleep(0.5)
