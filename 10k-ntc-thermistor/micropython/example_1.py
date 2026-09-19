# Runs on an ESP32 with MicroPython: samples ADC (GPIO34) in microvolts, computes the NTC resistance and converts it to temperature (°C/°F) using the beta formula.
#
# Buy this module: https://shillehtek.com/products/10k-ntc-thermistor-temperature-sensor-mf52-103
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/10k-ntc-thermistor-temperature-sensor-mf52-103-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MF52-103 10K NTC Thermistor - ESP32 MicroPython Example
# Divider: 3V3 - thermistor - GPIO34 - 10k - GND

from machine import ADC, Pin
import math, time

adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)

VCC      = 3.3
SERIES_R = 10000.0
NOMINAL  = 10000.0
B_COEFF  = 3950.0

def read_temp_c():
    total = 0
    for _ in range(20):
        total += adc.read_uv()
        time.sleep_ms(5)
    volts = total / 20 / 1_000_000

    r_ntc = SERIES_R * (VCC / volts - 1.0)     # thermistor on top
    steinhart = (math.log(r_ntc / NOMINAL) / B_COEFF
                 + 1.0 / (25.0 + 273.15))
    return 1.0 / steinhart - 273.15

print("MF52-103 thermistor ready")
while True:
    c = read_temp_c()
    print("Temperature: {:.1f} C / {:.1f} F".format(c, c * 9 / 5 + 32))
    time.sleep(1)
