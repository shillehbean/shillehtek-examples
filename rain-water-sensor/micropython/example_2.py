# On a Raspberry Pi Pico running MicroPython, briefly powers the probe from a GPIO, reads the 16-bit ADC value, determines dry/low/HIGH water state, and prints the result repeatedly.
#
# Buy this module: https://shillehtek.com/products/sensor-rain-water-level-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sensor-rain-water-level-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Water Level Sensor - Pico MicroPython Example (GPIO-powered)
# S -> GP26 (ADC0), + -> GP16, - -> GND

from machine import ADC, Pin
import time

power = Pin(16, Pin.OUT, value=0)   # sensor off between readings
adc = ADC(26)

def read_level():
    power.value(1)                  # energize the probe
    time.sleep_ms(20)               # settle
    value = adc.read_u16()          # 0-65535
    power.value(0)                  # off - no electrolysis
    return value

while True:
    level = read_level()

    if level < 6000:
        state = "dry"
    elif level < 28000:
        state = "low water"
    else:
        state = "HIGH water!"

    print("Raw: {} ({})".format(level, state))
    time.sleep(3)
