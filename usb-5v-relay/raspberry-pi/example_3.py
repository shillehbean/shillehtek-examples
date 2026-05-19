# Raspberry Pi Python example (pyserial) that pulses the relay ON for 5 seconds by writing the ON command to /dev/ttyUSB0, then writes the OFF command and closes the port.
#
# Buy this module: https://shillehtek.com/products/usb-control-module-1-channel-5v-relay-module-no-driver-needed
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/usb-control-module-1-channel-5v-relay-module-no-driver-needed-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Plug the relay into any USB port on the Pi
# It enumerates as /dev/ttyUSB0 (or similar)

import serial, time

ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(0.1)

# Pulse on for 5 seconds
ser.write(bytes([0xA0, 0x01, 0x01, 0xA2]))
time.sleep(5)
ser.write(bytes([0xA0, 0x01, 0x00, 0xA1]))
ser.close()
