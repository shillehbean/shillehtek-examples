# Uses MicroPython on a Pico to sample the MAX9814 analog output for 50 ms, compute the peak-to-peak sound level, and print the result.
#
# Buy this module: https://shillehtek.com/products/max9814-microphone-agc-amplifier-module-pre-soldered-header
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max9814-microphone-agc-amplifier-module-pre-soldered-header-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MAX9814 microphone amplifier on Raspberry Pi Pico (MicroPython) - print the sound level
# Wiring: Vdd = 3V3(OUT), GND = GND, Out = GP26 (ADC0)
from machine import ADC, Pin
import time

mic = ADC(Pin(26))
WINDOW_MS = 50            # listen for 50 ms per reading

while True:
    lowest = 65535
    highest = 0
    start = time.ticks_ms()
    while time.ticks_diff(time.ticks_ms(), start) < WINDOW_MS:
        value = mic.read_u16()        # 0 to 65535
        lowest = min(lowest, value)
        highest = max(highest, value)
    print("Sound level:", highest - lowest)
