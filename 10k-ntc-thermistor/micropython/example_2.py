# Example for a Raspberry Pi Pico running MicroPython: samples the 16-bit ADC (GP26), computes the thermistor resistance from the divider, and converts it to temperature using the beta equation.
#
# Buy this module: https://shillehtek.com/products/10k-ntc-thermistor-temperature-sensor-mf52-103
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/10k-ntc-thermistor-temperature-sensor-mf52-103-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MF52-103 10K NTC Thermistor - Pico MicroPython Example
# Divider: 3V3 - thermistor - GP26 - 10k - GND

from machine import ADC
import math, time

adc = ADC(26)
VCC, SERIES_R, NOMINAL, B_COEFF = 3.3, 10000.0, 10000.0, 3950.0

def read_temp_c():
    total = 0
    for _ in range(20):
        total += adc.read_u16()
        time.sleep_ms(5)
    volts = total / 20 / 65535 * VCC

    r_ntc = SERIES_R * (VCC / volts - 1.0)
    steinhart = (math.log(r_ntc / NOMINAL) / B_COEFF
                 + 1.0 / (25.0 + 273.15))
    return 1.0 / steinhart - 273.15

print("MF52-103 thermistor ready")
while True:
    c = read_temp_c()
    print("Temperature: {:.1f} C / {:.1f} F".format(c, c * 9 / 5 + 32))
    time.sleep(1)
