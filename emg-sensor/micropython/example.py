# On a Pico running MicroPython, sample the EMG input on GP26 (ADC0), convert the 16-bit scaled reading to volts, and print raw/voltage with a flex threshold.
#
# Buy this module: https://shillehtek.com/products/emg-muscle-signal-sensor-module-kit-for-arduino-robotics
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/emg-muscle-signal-sensor-module-kit-for-arduino-robotics-manual
# More examples: https://github.com/shillehtek/examples
#

# ShillehTek EMG Sensor - Pico MicroPython Example
# Reads the EMG SIG line on GP26 (ADC0).
# The Pico ADC is 12-bit but read_u16() scales it to 0..65535.

from machine import ADC, Pin
import time

emg = ADC(Pin(26))       # GP26 = ADC0
FLEX_THRESHOLD = 40000   # tune by watching your rest reading

while True:
    raw = emg.read_u16()
    voltage = raw * 3.3 / 65535
    label = "FLEX!" if raw > FLEX_THRESHOLD else ""
    print("EMG: {:5d}  ({:.2f} V)  {}".format(raw, voltage, label))
    time.sleep(0.02)
