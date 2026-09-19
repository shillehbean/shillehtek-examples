# Runs on an ESP32 with MicroPython: configures ADC on GPIO34 with 11dB attenuation, averages factory-calibrated microvolt readings (adc.read_uv()), converts to millivolts, estimates UV index as mV/100, and prints the result.
#
# Buy this module: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/uv-sensor-guva-s12sd-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# GUVA-S12SD UV Sensor - ESP32 MicroPython Example
# SIG Pin: GPIO 34 (ADC1_CH6), VCC: 3.3V, GND: GND
# UV Index is approximately the output voltage in mV divided by 100

from machine import ADC, Pin
import time

adc = ADC(Pin(34))        # GPIO 34: input-only pin on ADC1
adc.atten(ADC.ATTN_11DB)  # Full 0-3.3V input range

while True:
    # Average several readings to smooth out ADC noise
    total_uv = 0
    for _ in range(16):
        total_uv += adc.read_uv()  # Factory-calibrated reading in microvolts
        time.sleep_ms(2)
    millivolts = total_uv / 16 / 1000

    # Approximate solar UV Index: mV / 100
    uv_index = millivolts / 100

    print("Voltage: {:.0f} mV | UV Index: {:.1f}".format(millivolts, uv_index))
    time.sleep(1)
