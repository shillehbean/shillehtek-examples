# Sequentially pulse a list of safe output GPIO pins so you can verify each labeled terminal with an LED or voltage probe.
#
# Buy this module: https://shillehtek.com/products/esp32-38-pin-gpio-expansion-breakout
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-38-pin-gpio-expansion-breakout-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

# Pulses each safe output pin in turn - follow along with an LED
# probe on the breakout terminals to verify every label.
SAFE_PINS = [4, 5, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33]

pins = [Pin(n, Pin.OUT, value=0) for n in SAFE_PINS]

while True:
    for n, p in zip(SAFE_PINS, pins):
        print("GPIO", n)
        p.value(1)
        time.sleep(0.4)
        p.value(0)
        time.sleep(0.1)
