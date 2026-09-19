# Uses MicroPython PWM on pin 15 to vary pump flow by setting duty cycle (50% for 2s, 100% for 5s, then stop), suitable when the pump gate is driven through a MOSFET.
#
# Buy this module: https://shillehtek.com/products/mini-submersible-water-pump-3-5v-arduino-raspberry
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-submersible-water-pump-3-5v-arduino-raspberry-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Vary pump speed with PWM through the MOSFET.
# Gate on GP15 (Pico) / GPIO 15 (ESP32).

from machine import Pin, PWM
import time

pump = PWM(Pin(15))
pump.freq(1000)

def set_flow(percent):
    pump.duty_u16(int(65535 * percent / 100))

# Gentle start, full flow, then stop
set_flow(50)
time.sleep(2)
set_flow(100)
time.sleep(5)
set_flow(0)
print("Done")
