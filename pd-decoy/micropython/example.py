# Runs on a Pico with MicroPython to sample VBUS via ADC0, compute the actual output voltage from the divider, and print the voltage and detected PD profile every second.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pdsink-pd-decoy-pd-fast-charging-test-board-5-20v-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Pico PD Decoy voltage monitor
# VBUS -- 1M -- GP26 (ADC0) -- 100k -- GND

from machine import ADC
import time

adc = ADC(0)
divider_ratio = 11.0
v_ref = 3.3

while True:
    raw = adc.read_u16()
    v_adc = (raw / 65535) * v_ref
    v_out = v_adc * divider_ratio

    if v_out > 18.5:   profile = "20V"
    elif v_out > 13.5: profile = "15V"
    elif v_out > 10.5: profile = "12V"
    elif v_out >  7.5: profile = "9V"
    elif v_out >  4.0: profile = "5V"
    else:              profile = "none"

    print("Output: {:.2f} V ({})".format(v_out, profile))
    time.sleep(1)
