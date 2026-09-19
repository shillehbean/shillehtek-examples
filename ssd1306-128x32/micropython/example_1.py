# Scans I2C, initializes the SSD1306 on an ESP32 running MicroPython, and repeatedly draws a counter and a moving bar on the OLED.
#
# Buy this module: https://shillehtek.com/products/oled-ssd1306-128x32-i2c-0-91in
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/oled-ssd1306-128x32-i2c-0-91in-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 0.91" SSD1306 128x32 I2C OLED - ESP32 MicroPython Example
# SDA->GPIO 21, SCL->GPIO 22, VCC->3V3
# The ssd1306 module ships with MicroPython; if missing:
#   import mip; mip.install("ssd1306")

from machine import Pin, SoftI2C
import ssd1306
import time

i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])

oled = ssd1306.SSD1306_I2C(128, 32, i2c, addr=0x3C)

count = 0
while True:
    oled.fill(0)
    oled.text("ESP32 128x32", 0, 0)
    oled.text("N = {}".format(count), 0, 12)
    bar = (count * 4) % 128
    oled.fill_rect(0, 30, bar, 2, 1)
    oled.show()
    count += 1
    time.sleep(0.2)
