# MicroPython script for Raspberry Pi Pico that reads the divided LiPo voltage on GP26 (ADC0), averages samples, converts to the cell voltage, prints state-of-charge, and warns when near empty.
#
# Buy this module: https://shillehtek.com/products/3.7V
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/351015-500mah-3-7v-lithium-rechargeable-battery-3-5-x-10-x-15mm-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 351015 LiPo cell voltage monitor for Raspberry Pi Pico (MicroPython)
# Wiring: Cell (+) -- 100k -- GP26/ADC0 -- 100k -- GND
# Pico ADC is 12-bit, 3.3V reference, exposed via machine.ADC().read_u16()

from machine import ADC, Pin
import time

adc = ADC(Pin(26))            # ADC0 on GP26
VREF    = 3.3
DIVIDER = 2.0                 # R1 = R2 = 100k

def read_cell_voltage():
    total = 0
    for _ in range(32):
        total += adc.read_u16()  # 0..65535
        time.sleep_ms(2)
    raw = total / 32
    vpin = (raw / 65535) * VREF
    return vpin * DIVIDER

def state_of_charge(v):
    pct = (v - 3.0) / 1.2 * 100
    return max(0, min(100, pct))

while True:
    v = read_cell_voltage()
    soc = state_of_charge(v)
    print("LiPo: {:.2f} V  ({:.0f}%)".format(v, soc))
    if v < 3.1:
        print("WARNING: cell near empty - stop discharge.")
    time.sleep(2)
