# Uses aplay to play a WAV file while incrementally adjusting ALSA Master volume with amixer to exercise the amplifier output on a Raspberry Pi audio device.
#
# Buy this module: https://shillehtek.com/products/pam8406-stereo-class-d-amplifier-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pam8406-stereo-class-d-amplifier-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# PAM8406 Amplifier - Raspberry Pi Example
# Audio out (3.5mm or USB dongle) -> INL/INR/GND, VCC -> 5V
# Plays a test file and sweeps the system volume.
# Install: sudo apt install alsa-utils; put test.wav in the same folder

import subprocess
import time

def set_volume(percent):
    subprocess.run(
        ["amixer", "sset", "Master", "{}%".format(percent)],
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

print("Sweeping volume up while playing test.wav...")
player = subprocess.Popen(["aplay", "test.wav"])

try:
    vol = 20
    while player.poll() is None:
        set_volume(vol)
        print("Volume: {}%".format(vol))
        vol = min(90, vol + 10)
        time.sleep(1)
    print("Done.")
except KeyboardInterrupt:
    player.terminate()
    print("Stopped by user")
