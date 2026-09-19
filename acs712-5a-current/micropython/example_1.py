# ESP32 MicroPython script that reads the ACS712 via ADC (with a voltage divider), calibrates the zero offset, and prints measured voltage and DC current.
#
# Buy this module: https://shillehtek.com/products/acs712-current-sensor-5a-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/acs712-current-sensor-5a-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ACS712 5A Current Sensor - ESP32 MicroPython Example (DC current)
# OUT -> 10k/20k divider -> GPIO 34, VCC -> VIN (5V)
# Divider scales 5V -> 3.33V, so multiply measured volts by 1.5

from machine import ADC, Pin
import time

adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)      # full 0-3.3V range

SENSITIVITY = 0.185           # volts per amp (5A version)
DIVIDER = 1.5                 # (10k + 20k) / 20k

def read_volts(samples):
    total = 0
    for _ in range(samples):
        total += adc.read_uv()
        time.sleep_ms(1)
    return total / samples / 1_000_000 * DIVIDER

# Calibrate the zero point - no load current for these 2 seconds!
print("Calibrating zero point, keep load OFF...")
zero = read_volts(500)
print("Zero = {:.3f} V. Measuring...".format(zero))

while True:
    volts = read_volts(100)
    amps = (volts - zero) / SENSITIVITY
    print("OUT: {:.3f} V | Current: {:.3f} A".format(volts, amps))
    time.sleep(0.5)
