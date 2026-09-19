# Raspberry Pi example using the pyfingerprint Python library to open the serial device, verify the sensor, capture fingerprint images, convert them to characteristics, and search the onboard template database for matches.
#
# Buy this module: https://shillehtek.com/products/fingerprint-sensor-r307s-optical-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fingerprint-sensor-r307s-optical-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# R307S Fingerprint Sensor - Raspberry Pi Example
# Sensor TXD -> GPIO 15 (pin 10), Sensor RXD -> GPIO 14 (pin 8)
# Setup: sudo raspi-config (disable serial console, enable serial port)
#        pip3 install pyfingerprint

import time
from pyfingerprint.pyfingerprint import PyFingerprint

# Open the Pi's GPIO UART at the sensor's default settings
f = PyFingerprint('/dev/serial0', 57600, 0xFFFFFFFF, 0x00000000)

if not f.verifyPassword():
    raise ValueError('Sensor password check failed - check wiring/baud')

print('Sensor found. Templates used: {}/{}'.format(
    f.getTemplateCount(), f.getStorageCapacity()))
print('Place an enrolled finger on the window (Ctrl+C to stop)...')

try:
    while True:
        # Wait for a finger and capture the image
        if f.readImage():
            # Convert to characteristics in char buffer 1
            f.convertImage(0x01)

            # Search the template library
            position, accuracy = f.searchTemplate()

            if position >= 0:
                print('Match! Template #{} (accuracy {})'.format(
                    position, accuracy))
                time.sleep(1)
            else:
                print('No match for this finger.')
                time.sleep(0.5)
        time.sleep(0.05)

except KeyboardInterrupt:
    print('Stopped by user')
