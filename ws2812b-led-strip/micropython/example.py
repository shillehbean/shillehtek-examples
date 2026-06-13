# Demonstrates driving a 30-LED WS2812B strip from a Raspberry Pi Pico using a PIO state machine in MicroPython and a simple HSV-based rainbow routine.
#
# Buy this module: https://shillehtek.com/products/Addressable LED
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30-manual
# More examples: https://github.com/shillehtek/examples
#

# WS2812B Strip - Pico MicroPython with PIO
# DIN on GP0, 30 LEDs

import array
import time
from machine import Pin
import rp2

NUM_LEDS = 30
PIN_NUM  = 0

@rp2.asm_pio(sideset_init=rp2.PIO.OUT_LOW, out_shiftdir=rp2.PIO.SHIFT_LEFT,
             autopull=True, pull_thresh=24)
def ws2812():
    T1, T2, T3 = 2, 5, 3
    wrap_target()
    label("bitloop")
    out(x, 1)              .side(0)    [T3 - 1]
    jmp(not_x, "do_zero")  .side(1)    [T1 - 1]
    jmp("bitloop")         .side(1)    [T2 - 1]
    label("do_zero")
    nop()                  .side(0)    [T2 - 1]
    wrap()

sm = rp2.StateMachine(0, ws2812, freq=8_000_000, sideset_base=Pin(PIN_NUM))
sm.active(1)

ar = array.array("I", [0] * NUM_LEDS)

def show():
    for i in range(NUM_LEDS):
        sm.put(ar[i], 8)

def set_pixel(i, r, g, b):
    ar[i] = (g << 16) | (r << 8) | b   # GRB order

# Rainbow loop
hue = 0
while True:
    for i in range(NUM_LEDS):
        h = (hue + i * 8) % 360
        # naive HSV to RGB
        r = int(255 * max(0, min(1, abs((h/60) % 6 - 3) - 1)))
        g = int(255 * max(0, min(1, abs((h/60 + 4) % 6 - 3) - 1)))
        b = int(255 * max(0, min(1, abs((h/60 + 2) % 6 - 3) - 1)))
        set_pixel(i, r // 4, g // 4, b // 4)
    show()
    hue = (hue + 5) % 360
    time.sleep_ms(30)
