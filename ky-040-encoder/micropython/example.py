# MicroPython example for RP2040 (Pico) using pin IRQs to track encoder rotations and print counts and button presses with simple debouncing.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-040-rotary-encoder-module-for-arduino-with-demo-code-manual
# More examples: https://github.com/shillehtek/examples
#

# KY-040 Rotary Encoder - Pico MicroPython Example
# CLK=GP15, DT=GP14, SW=GP13

from machine import Pin
import time

clk = Pin(15, Pin.IN, Pin.PULL_UP)
dt  = Pin(14, Pin.IN, Pin.PULL_UP)
sw  = Pin(13, Pin.IN, Pin.PULL_UP)

counter = 0
last_clk = clk.value()

def on_rotate(pin):
    global counter, last_clk
    cur = clk.value()
    if cur != last_clk and cur == 0:
        if dt.value() != cur:
            counter += 1
        else:
            counter -= 1
    last_clk = cur

clk.irq(trigger=Pin.IRQ_FALLING | Pin.IRQ_RISING, handler=on_rotate)

last_print = counter
while True:
    if counter != last_print:
        print("Count:", counter)
        last_print = counter
    if sw.value() == 0:
        print("Button pressed!")
        time.sleep_ms(200)
    time.sleep_ms(10)
