# MicroPython example (e.g., Raspberry Pi Pico) that reads the AD8232 OUTPUT on ADC GP26 and prints a 12-bit-like sample or 0 if LO+ / LO- indicate an electrode is loose, at ~500 Hz.
#
# Buy this module: https://shillehtek.com/products/ecg-electrode-pads-ad8232-5-pack
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ecg-electrode-pads-ad8232-5-pack-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import ADC, Pin
import time

ecg = ADC(26)                    # AD8232 OUTPUT -> GP26
lo_plus = Pin(14, Pin.IN)        # LO+ -> GP14
lo_minus = Pin(15, Pin.IN)       # LO- -> GP15

while True:
    if lo_plus.value() or lo_minus.value():
        print(0)                 # electrode off
    else:
        print(ecg.read_u16() >> 4)   # 12-bit-ish value
    time.sleep_ms(2)
