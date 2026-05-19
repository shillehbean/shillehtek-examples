# Uses the RPLCD library on a Raspberry Pi to initialize a PCF8574-backed 16x2 LCD and write two lines of text.
#
# Buy this module: https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install RPLCD smbus2
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

from RPLCD.i2c import CharLCD

lcd = CharLCD('PCF8574', 0x27, port=1, cols=16, rows=2)
lcd.write_string('Hello, ShillehTek!')
lcd.crlf()
lcd.write_string('PCF8574 I2C LCD')
