# Open a serial connection to the FT232RL with pyserial and print any incoming lines from the connected device to the terminal.
#
# Buy this module: https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Read lines from any device connected to the FT232RL.
# Install dependency: pip install pyserial

import serial
import time

# Replace with your port:
#   Linux/macOS: '/dev/ttyUSB0' (Linux) or '/dev/tty.usbserial-XXXX' (macOS)
#   Windows:    'COM3', 'COM4', etc.
PORT = '/dev/ttyUSB0'
BAUD = 9600

with serial.Serial(PORT, BAUD, timeout=1) as ser:
    time.sleep(2)  # let the device reset on DTR toggle
    print(f"Listening on {PORT} at {BAUD} baud. Ctrl+C to stop.")
    try:
        while True:
            line = ser.readline().decode('utf-8', errors='replace').rstrip()
            if line:
                print(line)
    except KeyboardInterrupt:
        print("\nStopped.")
