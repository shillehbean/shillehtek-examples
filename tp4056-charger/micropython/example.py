# Runs on a Raspberry Pi Pico with MicroPython to sample the ADC (GP26/ADC0) through a 2:1 divider, calculate cell voltage, classify the charge level, and print it repeatedly.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tp4056-1a-lipo-battery-charging-board-type-c-with-current-protection-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Pico TP4056 voltage monitor
# Divider: OUT+ -- 100k -- GP26 (ADC0) -- 100k -- GND

from machine import ADC
import time

adc = ADC(0)
divider_ratio = 2.0
v_ref = 3.3

while True:
    raw = adc.read_u16()
    v_adc = (raw / 65535) * v_ref
    v_bat = v_adc * divider_ratio

    if v_bat > 4.15:
        state = "FULL"
    elif v_bat > 3.7:
        state = "GOOD"
    elif v_bat > 3.3:
        state = "LOW"
    else:
        state = "CRITICAL"

    print("Cell: {:.2f} V -- {}".format(v_bat, state))
    time.sleep(1)
