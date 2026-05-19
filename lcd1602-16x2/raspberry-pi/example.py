# Uses the RPLCD library on a Raspberry Pi (BCM pin numbering) to display two lines of text and update a running time value on the second row, cleaning up GPIO on exit.
#
# Buy this module: https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lcd1602-16x2-character-display-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# LCD1602 16x2 LCD Display - Raspberry Pi Example
# Uses RPLCD library: pip install RPLCD

from RPLCD.gpio import CharLCD
from RPi import GPIO
import time

lcd = CharLCD(
    pin_rs=25,
    pin_e=24,
    pins_data=[23, 17, 27, 22],
    numbering_mode=GPIO.BCM,
    cols=16,
    rows=2,
    dotsize=8
)

try:
    lcd.write_string("Hello, World!")
    lcd.cursor_pos = (1, 0)
    lcd.write_string("ShillehTek LCD")
    while True:
        lcd.cursor_pos = (1, 0)
        lcd.write_string("Time: {:>4}s   ".format(int(time.time()) % 10000))
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    lcd.close(clear=True)
    GPIO.cleanup()
