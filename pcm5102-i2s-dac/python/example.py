# Creates a 2-second 440 Hz stereo WAV file and plays it with aplay on a Raspberry Pi configured to use the PCM5102 (via the hifiberry-dac overlay).
#
# Buy this module: https://shillehtek.com/products/pcm5102-i2s-stereo-dac-presoldered-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcm5102-i2s-stereo-dac-presoldered-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# PCM5102 I2S DAC on Raspberry Pi - create a test tone and play it
# One-time setup in /boot/firmware/config.txt: put a # in front of dtparam=audio=on,
# add the line dtoverlay=hifiberry-dac, then reboot.
# Wiring: VIN = 5V (pin 2), GND = pin 6, SCK = GND, BCK = GPIO 18 (pin 12),
#         LCK = GPIO 19 (pin 35), DIN = GPIO 21 (pin 40)
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
    wav.setnchannels(2)         # stereo
    wav.setsampwidth(2)         # 16-bit samples
    wav.setframerate(RATE)
    wav.writeframes(bytes(frames))

subprocess.run(["aplay", "tone.wav"], check=True)
