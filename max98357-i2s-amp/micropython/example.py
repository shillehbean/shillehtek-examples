# Stream a 441 Hz sine-wave via MicroPython I2S on a Raspberry Pi Pico to the MAX98357 amplifier as a continuous test tone.
#
# Buy this module: https://shillehtek.com/products/max98357-i2s-class-d-amplifier-module-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max98357-i2s-class-d-amplifier-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MAX98357 I2S amplifier on Raspberry Pi Pico (MicroPython) - 441 Hz sine test tone
# Wiring: VIN = VBUS (5 V), GND = GND, BCLK = GP16, LRC = GP17, DIN = GP18
from machine import I2S, Pin
import math
import struct

RATE = 22050          # samples per second
FREQ = 441            # tone pitch in Hz (exactly 50 samples per wave at this rate)
VOLUME = 0.2          # 0.0 to 1.0

# On the Pico the LRC (ws) pin must be the GPIO right after the BCLK (sck) pin
audio = I2S(0, sck=Pin(16), ws=Pin(17), sd=Pin(18),
            mode=I2S.TX, bits=16, format=I2S.MONO, rate=RATE, ibuf=4000)

samples_per_wave = RATE // FREQ
wave = bytearray(samples_per_wave * 2)
for n in range(samples_per_wave):
    value = int(32767 * VOLUME * math.sin(2 * math.pi * n / samples_per_wave))
    struct.pack_into("<h", wave, n * 2, value)

try:
    while True:
        audio.write(wave)       # waits until the samples are queued
except KeyboardInterrupt:
    audio.deinit()
