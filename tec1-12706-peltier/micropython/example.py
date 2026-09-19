# Uses PWM at 5 kHz on a microcontroller pin to apply proportional power to the Peltier for smoother cooling and reduced audible whine.
#
# Buy this module: https://shillehtek.com/products/peltier-module-tec1-12706-12v-40x40mm
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/peltier-module-tec1-12706-12v-40x40mm-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TEC1-12706 proportional power via logic-level MOSFET
# Gate -> GP15 (Pico) or GPIO 15 (ESP32); grounds shared.
# 5 kHz PWM avoids audible whine and slow thermal cycling.

from machine import Pin, PWM
import time

tec = PWM(Pin(15))
tec.freq(5000)

def set_power(percent):
    """0-100% of full cooling power."""
    duty = int(65535 * percent / 100)
    tec.duty_u16(duty)

# Ramp up gently, hold, then off
set_power(30)
time.sleep(10)
set_power(60)
time.sleep(10)
set_power(0)
