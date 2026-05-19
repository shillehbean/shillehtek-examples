# A MicroPython example that blinks the onboard LED (D0 / GPIO1) with 250 ms on/off intervals; requires the ESP32-S3 MicroPython firmware.
#
# Buy this module: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable-manual
# More examples: https://github.com/shillehtek/examples
#

# XIAO ESP32-S3 - MicroPython Hello World
# Flash the official MicroPython ESP32-S3 firmware first.

from machine import Pin
import time

led = Pin(1, Pin.OUT)   # D0 = GPIO1

while True:
    led.value(1)
    time.sleep_ms(250)
    led.value(0)
    time.sleep_ms(250)
