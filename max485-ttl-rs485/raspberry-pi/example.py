# Python script for Raspberry Pi that toggles a GPIO (DE/RE) to drive /dev/serial0 at 9600 baud, sends numbered messages, and listens for replies while printing received lines to the console.
#
# Buy this module: https://shillehtek.com/products/max485-ttl-rs485-converter-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max485-ttl-rs485-converter-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MAX485 RS-485 - Raspberry Pi Example
# RO->GPIO15(RXD), DI->GPIO14(TXD), RE+DE->GPIO17
# Install: pip3 install pyserial ; enable UART in raspi-config

import serial
import time
import RPi.GPIO as GPIO

DIR_PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(DIR_PIN, GPIO.OUT, initial=GPIO.LOW)

port = serial.Serial("/dev/serial0", 9600, timeout=0.2)

def send(msg):
    GPIO.output(DIR_PIN, GPIO.HIGH)
    time.sleep(0.0001)
    port.write((msg + "\n").encode())
    port.flush()
    time.sleep(0.002)                 # drain the UART FIFO
    GPIO.output(DIR_PIN, GPIO.LOW)

counter = 0
print("RS-485 node ready")
try:
    while True:
        send("PI MSG {}".format(counter))
        counter += 1

        t0 = time.time()
        while time.time() - t0 < 1.0:
            line = port.readline()
            if line:
                print("Received:", line.decode(errors="ignore").strip())
except KeyboardInterrupt:
    GPIO.cleanup()
    print("Stopped by user")
