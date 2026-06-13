# Runs on a Raspberry Pi Pico (MicroPython) to read ADC0 (GP26) through a 100k/100k divider, convert the 16-bit ADC reading to battery voltage, and print the voltage every second.
#
# Buy this module: https://shillehtek.com/products/18650
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1s-3-7v-3a-2mos-bms-li-ion-18650-battery-protection-board-manual
# More examples: https://github.com/shillehtek/examples
#

# Pico reads P+ through a 100k/100k divider on ADC0 (GP26)
# Connect: P+ -- 100k -- GP26 -- 100k -- GND

from machine import ADC, Pin
import time

adc = ADC(0)  # GP26
divider_ratio = 2.0
v_ref = 3.3

while True:
    raw = adc.read_u16()
    v_adc = (raw / 65535) * v_ref
    v_bat = v_adc * divider_ratio
    print("Battery: {:.2f} V".format(v_bat))
    time.sleep(1)
