# ESP32 MicroPython example that reads ADC1 (GPIO34) for analog intensity and the digital comparator on GPIO25, printing raw ADC, converted voltage, and flame status.
#
# Buy this module: https://shillehtek.com/products/flame-sensor-ky-026-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/flame-sensor-ky-026-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# KY-026 Flame Sensor - ESP32 MicroPython Example
# A0 -> GPIO 34, D0 -> GPIO 25, + -> 3V3, G -> GND

from machine import ADC, Pin
import time

# GPIO 34 is an ADC1 channel, so it keeps working with Wi-Fi on
analog = ADC(Pin(34))
analog.atten(ADC.ATTN_11DB)   # full 0 - 3.3V input range

digital = Pin(25, Pin.IN)     # comparator flame output

while True:
    raw = analog.read()               # 0 - 4095
    voltage = raw * 3.3 / 4095

    if digital.value() == 1:
        state = "FLAME DETECTED!"
    else:
        state = "No flame"

    print("Analog: {} ({:.2f} V)  |  {}".format(raw, voltage, state))
    time.sleep(0.5)
