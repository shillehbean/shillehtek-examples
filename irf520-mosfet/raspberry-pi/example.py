# Uses gpiozero.PWMOutputDevice on Raspberry Pi GPIO18 to cycle through a set of duty percentages (including off) at 1 kHz to control a connected load.
#
# Buy this module: https://shillehtek.com/products/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from gpiozero import PWMOutputDevice
from time import sleep

load = PWMOutputDevice(18, frequency=1000)  # GPIO 18, 1 kHz

try:
    while True:
        for pct in (0.2, 0.5, 0.8, 1.0, 0.0):
            load.value = pct
            print(f"Duty: {pct * 100:.0f}%")
            sleep(2)
except KeyboardInterrupt:
    load.off()
