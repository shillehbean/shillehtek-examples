# Desktop Python example using pyserial to send the relay ON command, wait 2 seconds, then send the OFF command and close the port.
#
# Buy this module: https://shillehtek.com/products/usb-control-module-1-channel-5v-relay-module-no-driver-needed
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/usb-control-module-1-channel-5v-relay-module-no-driver-needed-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install pyserial
# Find your port: pyserial-ports or check Device Manager

import serial
import time

PORT = 'COM3'        # Windows
# PORT = '/dev/tty.wchusbserial1410'  # macOS
# PORT = '/dev/ttyUSB0'                # Linux

ser = serial.Serial(PORT, 9600, timeout=1)
time.sleep(0.1)

ON  = bytes([0xA0, 0x01, 0x01, 0xA2])
OFF = bytes([0xA0, 0x01, 0x00, 0xA1])

print("Relay ON")
ser.write(ON)
time.sleep(2)

print("Relay OFF")
ser.write(OFF)

ser.close()
