# In MicroPython on ESP32, briefly powers the probe from a GPIO, reads the ADC (0-4095), classifies the level as dry/low/HIGH, and prints the reading in a loop.
#
# Buy this module: https://shillehtek.com/products/sensor-rain-water-level-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sensor-rain-water-level-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Water Level Sensor - ESP32 MicroPython Example (GPIO-powered)
# S -> GPIO 34, + -> GPIO 25, - -> GND

from machine import ADC, Pin
import time

power = Pin(25, Pin.OUT, value=0)   # sensor off between readings
adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)            # full 0-3.3V range

def read_level():
    power.value(1)                  # energize the probe
    time.sleep_ms(20)               # settle
    value = adc.read()              # 0-4095
    power.value(0)                  # off - no electrolysis
    return value

while True:
    level = read_level()

    if level < 400:
        state = "dry"
    elif level < 1800:
        state = "low water"
    else:
        state = "HIGH water!"

    print("Raw: {} ({})".format(level, state))
    time.sleep(3)
