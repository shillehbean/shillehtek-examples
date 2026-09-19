# Raspberry Pi (Python) example that builds and sends raw 10-byte DFPlayer command frames over /dev/serial0 (pyserial) to initialize the device, set volume, play/pause/skip tracks, and stop playback.
#
# Buy this module: https://shillehtek.com/products/mp3-player-module-tf-card-arduino-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mp3-player-module-tf-card-arduino-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MP3-TF-16P - Raspberry Pi Example (raw 10-byte frames)
# TX->GPIO15, RX(via 1k)->GPIO14 | Install: pip3 install pyserial

import serial, time

port = serial.Serial("/dev/serial0", 9600)

def cmd(command, param=0):
    hi, lo = (param >> 8) & 0xFF, param & 0xFF
    frame = [0x7E, 0xFF, 0x06, command, 0x00, hi, lo]
    checksum = -sum(frame[1:]) & 0xFFFF
    frame += [(checksum >> 8) & 0xFF, checksum & 0xFF, 0xEF]
    port.write(bytes(frame))
    time.sleep(0.2)

cmd(0x3F)          # init
time.sleep(1)
cmd(0x06, 20)      # volume 20 (0-30)
cmd(0x03, 1)       # play track 0001.mp3
print("Playing track 1 for 15 s...")
time.sleep(15)

cmd(0x0E)          # pause
print("Paused. Next track...")
time.sleep(1)
cmd(0x01)          # next
time.sleep(10)
cmd(0x16)          # stop
print("Done.")
