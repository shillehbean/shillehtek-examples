# MicroPython example for a Pico that initializes a PCF8574 I2C LCD using the i2c_lcd driver and displays two lines of text.
#
# Buy this module: https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd-manual
# More examples: https://github.com/shillehtek/examples
#

# PCF8574 LCD on Pico - MicroPython
# Save i2c_lcd.py and lcd_api.py from the dhylands/python_lcd repo to the Pico
# https://github.com/dhylands/python_lcd

from machine import I2C, Pin
from i2c_lcd import I2cLcd

I2C_ADDR = 0x27   # try 0x3F if blank
i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)

lcd = I2cLcd(i2c, I2C_ADDR, 2, 16)
lcd.putstr("Hello, ShillehTek!")
lcd.move_to(0, 1)
lcd.putstr("PCF8574 I2C LCD")
