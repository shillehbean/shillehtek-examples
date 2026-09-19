# On a MicroPython board (pins GP16 for MOSFET gate and GP14 for a pull-up button), keep the magnet energized until the button is pressed, release it for 3 seconds, then re-energize.
#
# Buy this module: https://shillehtek.com/products/electromagnet-solenoid-12v-3kg-p20-15
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/electromagnet-solenoid-12v-3kg-p20-15-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Simple electromagnetic lock: hold while button is NOT pressed.
# MOSFET gate -> GP16, button between GP14 and GND.

from machine import Pin
import time

magnet = Pin(16, Pin.OUT)
button = Pin(14, Pin.IN, Pin.PULL_UP)

magnet.value(1)          # locked at boot
print("Locked")

while True:
    if button.value() == 0:      # button pressed -> release
        magnet.value(0)
        print("Released")
        time.sleep(3)            # stay open 3 s
        magnet.value(1)
        print("Locked")
    time.sleep(0.05)
