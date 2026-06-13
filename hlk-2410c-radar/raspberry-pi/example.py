# Open a Linux serial port (e.g. /dev/serial0) on a Raspberry Pi with pyserial to read and buffer incoming HLK-2410C frames, then parse and print human-readable target state and distances.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410c-human-presence-radar-motion-detection-module-pre-soldered-manual
# More examples: https://github.com/shillehtek/examples
#

import serial
import time

ser = serial.Serial('/dev/serial0', 256000, timeout=0.1)
FOOTER = bytes([0xF8, 0xF7, 0xF6, 0xF5])

buf = bytearray()

print("HLK-2410C reader started. Ctrl-C to exit.")
try:
    while True:
        data = ser.read(64)
        if data:
            buf.extend(data)
            # Find a complete frame
            while FOOTER in buf:
                end = buf.index(FOOTER) + 4
                frame = bytes(buf[:end])
                del buf[:end]

                if len(frame) >= 17:
                    state = frame[8]
                    move = frame[9] | (frame[10] << 8)
                    static = frame[12] | (frame[13] << 8)
                    names = {0: "None", 1: "Moving", 2: "Static", 3: "Both"}
                    print(f"{names.get(state,'?'):6s}  move={move}cm  static={static}cm")
        time.sleep(0.05)
except KeyboardInterrupt:
    ser.close()
