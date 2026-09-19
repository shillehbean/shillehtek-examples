# Runs on a Raspberry Pi Pico with MicroPython to read GP26 (ADC0), average ADC readings, undo the voltage divider, compute wind speed in m/s and mph, and print the values.
#
# Buy this module: https://shillehtek.com/products/anemometer-wind-speed-0-5v-analog-output
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/anemometer-wind-speed-0-5v-analog-output-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Wind Speed Sensor (0-5V Anemometer) - Pico MicroPython Example
# Blue signal -> 10k/20k divider -> GP26 (ADC0), Brown -> 12V, Black -> GND
# Divider scales 5V -> 3.33V, so multiply the measured volts by 1.5

from machine import ADC
import time

adc = ADC(26)                 # GP26 = ADC0
CONVERSION = 3.3 / 65535      # read_u16() spans 0-65535 across 0-3.3V
DIVIDER_RATIO = 1.5           # (10k + 20k) / 20k

while True:
    # Average several readings to steady the value in gusty air
    total = 0
    for _ in range(16):
        total += adc.read_u16()
        time.sleep_ms(5)
    volts_at_pin = (total / 16) * CONVERSION

    signal_volts = volts_at_pin * DIVIDER_RATIO
    wind_ms = signal_volts * 6.0
    wind_mph = wind_ms * 2.237

    print("Signal: {:.2f} V | Wind: {:.1f} m/s ({:.1f} mph)".format(
        signal_volts, wind_ms, wind_mph))
    time.sleep(1)
