# Create a 2-second 440 Hz stereo WAV file and play it with aplay on a Raspberry Pi configured to use the MAX98357 I2S audio overlay.
#
# Buy this module: https://shillehtek.com/products/max98357-i2s-class-d-amplifier-module-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max98357-i2s-class-d-amplifier-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MAX98357 I2S amplifier on Raspberry Pi - create a test tone and play it
# One-time setup in /boot/firmware/config.txt: put a # in front of dtparam=audio=on,
# add the line dtoverlay=max98357a, then reboot.
# Wiring: VIN = 5V (pin 2), GND = pin 6, BCLK = GPIO 18 (pin 12),
#         LRC = GPIO 19 (pin 35), DIN = GPIO 21 (pin 40)
import math
import struct
import subprocess
import wave

RATE = 44100          # samples per second
FREQ = 440.0          # tone pitch in Hz
SECONDS = 2
VOLUME = 0.2          # 0.0 to 1.0

frames = bytearray()
for n in range(RATE * SECONDS):
    value = int(32767 * VOLUME * math.sin(2 * math.pi * FREQ * n / RATE))
    frames += struct.pack("<hh", value, value)      # left and right sample

with wave.open("tone.wav", "wb") as wav:
    wav.setnchannels(2)         # the Pi's I2S output expects stereo
    wav.setsampwidth(2)         # 16-bit samples
    wav.setframerate(RATE)
    wav.writeframes(bytes(frames))

subprocess.run(["aplay", "tone.wav"], check=True)
