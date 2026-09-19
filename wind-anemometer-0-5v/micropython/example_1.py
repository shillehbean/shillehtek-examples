# Runs on an ESP32 with MicroPython: reads the divided analog signal on GPIO34 using ADC read_uv(), compensates for a 10k/20k voltage divider, converts voltage to wind speed, and prints values.
#
# Buy this module: https://shillehtek.com/products/anemometer-wind-speed-0-5v-analog-output
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/anemometer-wind-speed-0-5v-analog-output-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Wind Speed Sensor (0-5V Anemometer) - ESP32 MicroPython Example
# Blue signal -> 10k/20k divider -> GPIO 34, Brown -> 12V, Black -> GND (shared)
# Divider scales 5V -> 3.33V, so multiply the measured volts by 1.5

from machine import ADC, Pin
import time

adc = ADC(Pin(34))        # ADC1 channel - keeps working with Wi-Fi on
adc.atten(ADC.ATTN_11DB)  # Full 0-3.3V input range

DIVIDER_RATIO = 1.5       # (10k + 20k) / 20k

while True:
    # Average several readings to steady the value in gusty air
    total_uv = 0
    for _ in range(16):
        total_uv += adc.read_uv()   # calibrated reading in microvolts
        time.sleep_ms(5)
    volts_at_pin = total_uv / 16 / 1_000_000

    # Undo the divider, then convert to wind speed
    signal_volts = volts_at_pin * DIVIDER_RATIO
    wind_ms = signal_volts * 6.0
    wind_mph = wind_ms * 2.237

    print("Signal: {:.2f} V | Wind: {:.1f} m/s ({:.1f} mph)".format(
        signal_volts, wind_ms, wind_mph))
    time.sleep(1)
