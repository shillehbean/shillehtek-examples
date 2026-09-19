# Uses MicroPython on a Raspberry Pi Pico to read the KY-018 on GP26 (ADC0), prints the 0–65535 raw reading and classifies ambient light as bright/dim/dark.
#
# Buy this module: https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/photoresistor-light-sensor-ky-018-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# KY-018 Photoresistor - Pico MicroPython Example
# S -> GP26 (ADC0), VCC (middle) -> 3V3(OUT), - -> GND

from machine import ADC
import time

adc = ADC(26)

while True:
    raw = adc.read_u16()    # 0-65535, higher = brighter

    if raw > 45000:
        state = "bright"
    elif raw > 20000:
        state = "dim"
    else:
        state = "dark"

    print("Light level: {} ({})".format(raw, state))
    time.sleep(0.5)
