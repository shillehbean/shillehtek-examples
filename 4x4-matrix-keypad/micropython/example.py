# Scans a 4x4 keypad on a Raspberry Pi Pico by driving row outputs and reading column inputs with pull-ups, printing each detected key press.
#
# Buy this module: https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy-manual
# More examples: https://github.com/shillehtek/examples
#

# 4x4 Keypad - Pico MicroPython
# Wire R1-R4 to GP9, GP8, GP7, GP6 / C1-C4 to GP5, GP4, GP3, GP2

from machine import Pin
import time

KEYS = [
    ['1','2','3','A'],
    ['4','5','6','B'],
    ['7','8','9','C'],
    ['*','0','#','D'],
]

rows = [Pin(p, Pin.OUT) for p in (9, 8, 7, 6)]
cols = [Pin(p, Pin.IN, Pin.PULL_UP) for p in (5, 4, 3, 2)]

def scan():
    for r_i, r in enumerate(rows):
        # Drive this row LOW, others HIGH
        for other in rows: other.value(1)
        r.value(0)
        time.sleep_ms(1)
        for c_i, c in enumerate(cols):
            if c.value() == 0:
                # Wait for release
                while c.value() == 0:
                    time.sleep_ms(5)
                return KEYS[r_i][c_i]
    return None

while True:
    k = scan()
    if k:
        print("Pressed:", k)
    time.sleep_ms(20)
