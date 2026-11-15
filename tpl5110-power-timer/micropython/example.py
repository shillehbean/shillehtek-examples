# MicroPython main.py for a Raspberry Pi Pico that performs work on wake and pulses the DONE pin (GP15) until the TPL5110 cuts power.
#
# Buy this module: https://shillehtek.com/products/tpl5110-timer-module-pre-soldered-header
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tpl5110-timer-module-pre-soldered-header-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TPL5110 power timer with a Raspberry Pi Pico (MicroPython) - save as main.py
# The Pico is powered from the TPL5110 DRV pin, so this script restarts at every wake-up.
# Wiring: Done = GP15, DRV = VSYS (pin 39), GND = GND
from machine import Pin
import time

done = Pin(15, Pin.OUT, value=0)

print("Awake - doing the job")
# Put your own work here: read a sensor, then send or store the result.
time.sleep(0.5)
print("Finished - asking the timer to cut power")

while True:               # pulse Done until the power disappears
    done.value(1)
    time.sleep_ms(1)
    done.value(0)
    time.sleep_ms(1)
