# On a Raspberry Pi Pico running MicroPython, reads ADC0 (GP26) through a 330k/100k divider, calculates the 2S pack voltage, and prints the voltage every second.
#
# Buy this module: https://shillehtek.com/products/18650
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx-2s-jh20-2s-7-4v-18650-lithium-battery-protection-board-10a-with-balancer-manual
# More examples: https://github.com/shillehtek/examples
#

# Pico reads pack voltage through a 330k/100k divider on ADC0 (GP26)
# 8.4V / 4.3 = 1.95V at ADC -- safely below 3.3V

from machine import ADC
import time

adc = ADC(0)
divider_ratio = 4.3
v_ref = 3.3

while True:
    raw = adc.read_u16()
    v_adc = (raw / 65535) * v_ref
    v_pack = v_adc * divider_ratio
    print("Pack: {:.2f} V".format(v_pack))
    time.sleep(1)
