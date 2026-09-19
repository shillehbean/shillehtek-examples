# Initializes I2C on a Raspberry Pi Pico under MicroPython and displays a counter plus a moving progress bar on the SSD1306 128x32 OLED.
#
# Buy this module: https://shillehtek.com/products/oled-ssd1306-128x32-i2c-0-91in
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/oled-ssd1306-128x32-i2c-0-91in-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 0.91" SSD1306 128x32 I2C OLED - Pico MicroPython Example
# SDA->GP4 (pin 6), SCL->GP5 (pin 7), VCC->3V3(OUT)
# In Thonny: Tools > Manage Packages > install "ssd1306" if needed

from machine import Pin, I2C
import ssd1306
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])

oled = ssd1306.SSD1306_I2C(128, 32, i2c, addr=0x3C)

count = 0
while True:
    oled.fill(0)
    oled.text("Pico 128x32", 0, 0)
    oled.text("N = {}".format(count), 0, 12)
    bar = (count * 4) % 128
    oled.fill_rect(0, 30, bar, 2, 1)
    oled.show()
    count += 1
    time.sleep(0.2)
