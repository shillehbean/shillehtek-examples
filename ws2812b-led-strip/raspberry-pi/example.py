# Uses the rpi_ws281x Python library on a Raspberry Pi to drive a 30-LED WS2812B strip and display a rotating color wheel animation.
#
# Buy this module: https://shillehtek.com/products/Addressable LED
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# WS2812B Strip - Raspberry Pi Example
# sudo pip install rpi_ws281x
# Run as root (sudo) because PWM access requires root.

import time
from rpi_ws281x import PixelStrip, Color

LED_COUNT      = 30
LED_PIN        = 18       # GPIO 18 (Pin 12, PWM0)
LED_FREQ_HZ    = 800000
LED_DMA        = 10
LED_BRIGHTNESS = 64        # 0 - 255
LED_INVERT     = False
LED_CHANNEL    = 0

strip = PixelStrip(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA,
                   LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
strip.begin()

def wheel(pos):
    if pos < 85:
        return Color(pos * 3, 255 - pos * 3, 0)
    elif pos < 170:
        pos -= 85
        return Color(255 - pos * 3, 0, pos * 3)
    else:
        pos -= 170
        return Color(0, pos * 3, 255 - pos * 3)

try:
    j = 0
    while True:
        for i in range(LED_COUNT):
            strip.setPixelColor(i, wheel((i * 256 // LED_COUNT + j) & 255))
        strip.show()
        j = (j + 1) % 256
        time.sleep(0.02)
except KeyboardInterrupt:
    for i in range(LED_COUNT):
        strip.setPixelColor(i, Color(0, 0, 0))
    strip.show()
