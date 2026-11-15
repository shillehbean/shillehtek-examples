# Streams a repeating 441 Hz sine-wave buffer over I2S from a Raspberry Pi Pico running MicroPython to the PCM5102 DAC.
#
# Buy this module: https://shillehtek.com/products/pcm5102-i2s-stereo-dac-presoldered-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcm5102-i2s-stereo-dac-presoldered-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# PCM5102 I2S DAC on Raspberry Pi Pico (MicroPython) - 441 Hz sine test tone
# Wiring: VIN = 3V3(OUT), GND = GND, SCK = GND, BCK = GP16, LCK = GP17, DIN = GP18
from machine import I2S, Pin
import math
import struct

RATE = 22050          # samples per second
FREQ = 441            # tone pitch in Hz (exactly 50 samples per wave at this rate)
VOLUME = 0.2          # 0.0 to 1.0

# On the Pico the LCK (ws) pin must be the GPIO right after the BCK (sck) pin
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
