# MicroPython example for the Raspberry Pi Pico that initializes the SSD1306 over I2C and writes static text to the 128×64 display.
#
# Buy this module: https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/0-96-i2c-white-oled-display-module-4-pin-ssd1306-manual
# More examples: https://github.com/shillehtek/examples
#

# 0.96" SSD1306 OLED - Pico MicroPython Example
# Upload ssd1306.py to the Pico (micropython-ssd1306 driver)
# Wiring: SDA -> GP4, SCL -> GP5

from machine import Pin, I2C
import ssd1306
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400_000)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

oled.fill(0)
oled.text("ShillehTek",   0, 0)
oled.text("SSD1306 OLED", 0, 16)
oled.text("128 x 64",     0, 32)
oled.show()

while True:
    time.sleep(1)
