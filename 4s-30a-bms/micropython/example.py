# Runs on a Raspberry Pi Pico (MicroPython) to read the 4S pack voltage on ADC0 (GP26) through the 680k/100k divider and prints the measured voltage once per second.
#
# Buy this module: https://shillehtek.com/products/14.8V
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4s-30a-18650-lithium-battery-protection-board-14-8v-16v-with-cable-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Pico reads 4S pack voltage through a 680k/100k divider on ADC0 (GP26)

from machine import ADC
import time

adc = ADC(0)
divider_ratio = 7.8
v_ref = 3.3

while True:
    raw = adc.read_u16()
    v_adc = (raw / 65535) * v_ref
    v_pack = v_adc * divider_ratio
    print("Pack: {:.2f} V".format(v_pack))
    time.sleep(1)
