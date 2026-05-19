# Demonstrates using a sh1106 MicroPython driver on a Raspberry Pi Pico (I2C) to write multiple lines of text to the 128x64 display.
#
# Buy this module: https://shillehtek.com/products/1-3-i2c-white-oled-display-module-4-pin-sh1106
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-3-i2c-white-oled-display-module-4-pin-sh1106-manual
# More examples: https://github.com/shillehtek/examples
#

# 1.3" SH1106 OLED - Pico MicroPython Example
# Upload sh1106.py to the Pico (micropython-sh1106 driver)
# Wiring: SDA -> GP4, SCL -> GP5

from machine import Pin, I2C
import sh1106
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400_000)
oled = sh1106.SH1106_I2C(128, 64, i2c, None, 0x3C)
oled.rotate(True)   # optional - flip 180 if orientation is off

oled.fill(0)
oled.text("ShillehTek",  0, 0)
oled.text("SH1106 OLED", 0, 16)
oled.text("128 x 64",    0, 32)
oled.show()

while True:
    time.sleep(1)
