# Raspberry Pi Pico MicroPython example reading ADC0 (GP26) for analog intensity and GP15 for the comparator output, printing raw ADC, voltage, and flame status.
#
# Buy this module: https://shillehtek.com/products/flame-sensor-ky-026-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/flame-sensor-ky-026-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# KY-026 Flame Sensor - Pico MicroPython Example
# A0 -> GP26 (ADC0), D0 -> GP15, + -> 3V3(OUT), G -> GND

from machine import ADC, Pin
import time

analog = ADC(26)            # GP26 = ADC0
digital = Pin(15, Pin.IN)   # comparator flame output

while True:
    raw = analog.read_u16()          # 0 - 65535
    voltage = raw * 3.3 / 65535

    if digital.value() == 1:
        state = "FLAME DETECTED!"
    else:
        state = "No flame"

    print("Analog: {} ({:.2f} V)  |  {}".format(raw, voltage, state))
    time.sleep(0.5)
