# A minimal Python script using pyserial that opens the CP2102 serial port at 115200 baud and continuously reads and prints incoming lines to the console.
#
# Buy this module: https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip3 install pyserial

import serial
import time

# Linux:  '/dev/ttyUSB0'
# macOS:  '/dev/cu.SLAB_USBtoUART'
# Windows: 'COM3' (check Device Manager)
PORT = '/dev/ttyUSB0'
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)
print(f"Connected to {PORT} @ {BAUD}")

while True:
    line = ser.readline().decode('utf-8', errors='replace').strip()
    if line:
        print(line)
