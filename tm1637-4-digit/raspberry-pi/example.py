# Raspberry Pi Python example using the tm1637 library to show a short text message and then count up from 0 to 9999 on the display.
#
# Buy this module: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-bits-tm1637-red-led-display-module-clock-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# TM1637 4-Digit Display - Raspberry Pi Example
# pip install raspberrypi-tm1637

import tm1637
import time

display = tm1637.TM1637(clk=17, dio=27)
display.brightness(4)

# Show "HELO" message
display.show("HELO")
time.sleep(2)

# Count up forever
try:
    for i in range(10000):
        display.number(i)
        time.sleep(0.1)
except KeyboardInterrupt:
    display.show("    ")  # blank
    print("Stopped")
