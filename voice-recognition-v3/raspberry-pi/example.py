# Uses pyserial on a Raspberry Pi to send raw protocol load commands for trained records and to read and parse recognition frames from the module over /dev/serial0.
#
# Buy this module: https://shillehtek.com/products/arduino-voice-recognition-module-v3
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-voice-recognition-module-v3-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# Voice Recognition Module V3 - Raspberry Pi Example (raw protocol)
# Module TXD -> GPIO 15 via divider, Module RXD -> GPIO 14, VCC -> 5V
# Setup: sudo raspi-config (disable serial console, enable serial port)
#        pip3 install pyserial
# Train the records first with an Arduino - they stay on the module.

import time
import serial

ser = serial.Serial('/dev/serial0', baudrate=9600, timeout=0.1)

def load_record(rec):
    # Frame: AA | LEN | 30 (load) | record | 0A
    ser.write(bytes([0xAA, 0x02, 0x30, rec, 0x0A]))
    time.sleep(0.05)

# Load trained records 0-2 into the active recognizer
for r in (0, 1, 2):
    load_record(r)

print('Speak one of your trained commands (Ctrl+C to stop)...')

buffer = bytearray()

try:
    while True:
        data = ser.read(32)
        if data:
            buffer.extend(data)

            # Complete frames start with 0xAA and end with 0x0A
            while 0xAA in buffer and 0x0A in buffer[buffer.index(0xAA):]:
                start = buffer.index(0xAA)
                end = buffer.index(0x0A, start)
                frame = buffer[start:end + 1]
                del buffer[:end + 1]

                # frame[2] == 0x0D means "voice recognized";
                # frame[4] holds the record number
                if len(frame) > 5 and frame[2] == 0x0D:
                    print('Recognized record #{}'.format(frame[4]))
        time.sleep(0.02)

except KeyboardInterrupt:
    print('Stopped by user')
finally:
    ser.close()
