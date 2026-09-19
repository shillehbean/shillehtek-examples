# Raspberry Pi Python script using the RPLCD library and RPi.GPIO in 4-bit GPIO mode to drive the 20x4 LCD, print multiple lines, and update an uptime counter with proper cleanup on Ctrl+C.
#
# Buy this module: https://shillehtek.com/products/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# LCD2004 20x4 Character LCD - Raspberry Pi Example (RPLCD, 4-bit GPIO)
# RS->GPIO26, E->GPIO19, D4-D7->GPIO13/6/5/11, RW->GND, VDD->5V
# Install: pip3 install RPLCD RPi.GPIO

import time
from RPLCD.gpio import CharLCD
import RPi.GPIO as GPIO

lcd = CharLCD(numbering_mode=GPIO.BCM,
              cols=20, rows=4,
              pin_rs=26, pin_e=19,
              pins_data=[13, 6, 5, 11],
              auto_linebreaks=True)

lcd.clear()
lcd.write_string("ShillehTek LCD2004")
lcd.cursor_pos = (1, 0)
lcd.write_string("Raspberry Pi + RPLCD")
lcd.cursor_pos = (2, 0)
lcd.write_string("20 columns x 4 rows")

count = 0
try:
    while True:
        lcd.cursor_pos = (3, 0)
        lcd.write_string("Uptime: {} s   ".format(count))
        count += 1
        time.sleep(1)
except KeyboardInterrupt:
    lcd.clear()
    GPIO.cleanup()
    print("Stopped by user")
