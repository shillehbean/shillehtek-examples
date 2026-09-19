# Raspberry Pi Pico MicroPython script that reads the ACS712 through the GP26 ADC (with a voltage divider), calibrates the zero offset, and prints measured voltage and DC current.
#
# Buy this module: https://shillehtek.com/products/acs712-current-sensor-5a-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/acs712-current-sensor-5a-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ACS712 5A Current Sensor - Pico MicroPython Example (DC current)
# OUT -> 10k/20k divider -> GP26 (ADC0), VCC -> VBUS (5V)

from machine import ADC
import time

adc = ADC(26)
CONVERSION = 3.3 / 65535
SENSITIVITY = 0.185        # volts per amp (5A version)
DIVIDER = 1.5              # (10k + 20k) / 20k

def read_volts(samples):
    total = 0
    for _ in range(samples):
        total += adc.read_u16()
        time.sleep_ms(1)
    return total / samples * CONVERSION * DIVIDER

print("Calibrating zero point, keep load OFF...")
zero = read_volts(500)
print("Zero = {:.3f} V. Measuring...".format(zero))

while True:
    volts = read_volts(100)
    amps = (volts - zero) / SENSITIVITY
    print("OUT: {:.3f} V | Current: {:.3f} A".format(volts, amps))
    time.sleep(0.5)
