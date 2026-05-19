# Reads the AD8232 output on a Raspberry Pi Pico ADC in MicroPython, handles leads-off detection, scales the 16-bit ADC reading to 12-bit, and prints values at ~200 Hz.
#
# Buy this module: https://shillehtek.com/products/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit-manual
# More examples: https://github.com/shillehtek/examples
#

# AD8232 ECG Module - Pico MicroPython Example
# OUTPUT -> GP26 (ADC0), LO+ -> GP14, LO- -> GP15

from machine import ADC, Pin
import time

ecg      = ADC(Pin(26))
lo_plus  = Pin(14, Pin.IN)
lo_minus = Pin(15, Pin.IN)

print("AD8232 ECG Demo")

while True:
    if lo_plus.value() or lo_minus.value():
        print(0)                        # leads off
    else:
        raw = ecg.read_u16()            # 0 - 65535
        print(raw >> 4)                 # scale down to 0 - 4095 (12-bit)
    time.sleep_ms(5)                    # ~200 Hz
