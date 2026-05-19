# Run on a Raspberry Pi Pico (MicroPython) to output a PWM signal on GP15 that the TXS0108E presents as a 5V PWM enable to a LED strip, sweeping brightness up and down.
#
# Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter-manual
# More examples: https://github.com/shillehtek/examples
#

# TXS0108E - Drive a 5V LED strip enable line from Pico
# Pico GP15 -> A1, B1 -> 5V LED strip enable
# VA = 3V3 (Pin 36), VB = VBUS (Pin 40), OE = 3V3

from machine import Pin, PWM
import time

# 5V output via TXS0108E channel 1
led_enable = PWM(Pin(15))
led_enable.freq(1000)

# Sweep brightness 0% -> 100% -> 0%
while True:
    for duty in range(0, 65536, 1024):
        led_enable.duty_u16(duty)
        time.sleep_ms(10)
    for duty in range(65535, -1, -1024):
        led_enable.duty_u16(duty)
        time.sleep_ms(10)
