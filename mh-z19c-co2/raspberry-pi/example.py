# Opens /dev/serial0 at 9600 baud on a Raspberry Pi, sends the MH-Z19C read command, checks the response checksum, and prints CO2 ppm periodically.
#
# Buy this module: https://shillehtek.com/products/co2-sensor-mh-z19c-ndir-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/co2-sensor-mh-z19c-ndir-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MH-Z19C CO2 Sensor - Raspberry Pi Example (raw UART protocol)
# Sensor Tx -> GPIO 15 (pin 10), Sensor Rx -> GPIO 14 (pin 8), Vin -> 5V
# Setup: sudo raspi-config (disable serial console, enable serial port)
#        pip3 install pyserial

import time
import serial

READ_CMD = bytes([0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79])

ser = serial.Serial('/dev/serial0', baudrate=9600, timeout=1)

print('Warming up (about 60 s after power-on)...')

try:
    while True:
        ser.reset_input_buffer()
        ser.write(READ_CMD)
        response = ser.read(9)

        if len(response) == 9 and response[0] == 0xFF and response[1] == 0x86:
            checksum = (0xFF - (sum(response[1:8]) & 0xFF) + 1) & 0xFF
            if checksum == response[8]:
                ppm = response[2] * 256 + response[3]
                print('CO2: {} ppm'.format(ppm))
            else:
                print('Checksum error - reading discarded')
        else:
            print('No response - check wiring and 5V supply')

        time.sleep(5)

except KeyboardInterrupt:
    print('Stopped by user')
finally:
    ser.close()
