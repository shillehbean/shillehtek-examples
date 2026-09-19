# Uses MicroPython on an ESP32 to read the KY-018 on GPIO34 via ADC, prints the 0–4095 raw value and a bright/dim/dark classification.
#
# Buy this module: https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/photoresistor-light-sensor-ky-018-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# KY-018 Photoresistor - ESP32 MicroPython Example
# S -> GPIO 34, VCC (middle) -> 3V3, - -> GND

from machine import ADC, Pin
import time

adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)   # full 0-3.3V range

while True:
    raw = adc.read()        # 0-4095, higher = brighter

    if raw > 2800:
        state = "bright"
    elif raw > 1200:
        state = "dim"
    else:
        state = "dark"

    print("Light level: {} ({})".format(raw, state))
    time.sleep(0.5)
