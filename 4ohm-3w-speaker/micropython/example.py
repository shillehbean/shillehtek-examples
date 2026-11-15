# MicroPython script that outputs a 441 Hz sine wave via I2S (configurable pins for ESP32 or Pico) to drive a digital amplifier like the MAX98357 for about two seconds.
#
# Buy this module: https://shillehtek.com/products/mini-speaker-4ohm-3w-square-150mm-dupont-lead
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-speaker-4ohm-3w-square-150mm-dupont-lead-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# I2S test tone - MicroPython with a MAX98357 amplifier
# ESP32 pins: BCLK = 26, LRC = 25, DIN = 22
# Pico pins:  BCLK = 16, LRC = 17, DIN = 18  (LRC must be BCLK + 1)
from machine import I2S, Pin
import math
import struct

BCLK, LRC, DIN = 26, 25, 22   # change to 16, 17, 18 on a Pico

RATE = 22050      # samples per second
FREQ = 441        # Hz - exactly 50 samples per cycle at 22050
VOLUME = 0.25     # 0.0 to 1.0, start low

audio = I2S(0, sck=Pin(BCLK), ws=Pin(LRC), sd=Pin(DIN),
            mode=I2S.TX, bits=16, format=I2S.MONO,
            rate=RATE, ibuf=4000)

# Build one cycle of a sine wave as 16-bit samples
n = RATE // FREQ
cycle = bytearray(n * 2)
for i in range(n):
    sample = int(32767 * VOLUME * math.sin(2 * math.pi * i / n))
    struct.pack_into("<h", cycle, i * 2, sample)

try:
    for _ in range(FREQ * 2):     # about 2 seconds of tone
        audio.write(cycle)
finally:
    audio.deinit()
