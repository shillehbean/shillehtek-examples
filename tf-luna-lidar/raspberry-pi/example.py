# Raspberry Pi Python script using pyserial to read TF-Luna frames from /dev/serial0, validate checksums, and return distance, signal strength, and temperature in a loop.
#
# Buy this module: https://shillehtek.com/products/lidar-tf-luna-single-module-8m
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lidar-tf-luna-single-module-8m-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# TF-Luna LiDAR on Raspberry Pi over UART (GPIO 14 = TXD, GPIO 15 = RXD)
# Install once: sudo apt install python3-serial
# raspi-config -> Interface Options -> Serial Port: login shell NO, serial hardware YES
import time
import serial

port = serial.Serial("/dev/serial0", 115200, timeout=1)


def read_frame():
    """Return (distance_cm, strength, temp_c), or None if no valid frame arrived."""
    if port.read(1) != b"Y":            # 0x59, first header byte
        return None
    if port.read(1) != b"Y":            # 0x59, second header byte
        return None
    body = port.read(7)
    if len(body) != 7:
        return None
    if (0x59 + 0x59 + sum(body[:6])) & 0xFF != body[6]:
        return None                     # checksum mismatch
    distance = body[0] | (body[1] << 8)
    strength = body[2] | (body[3] << 8)
    temp_c = (body[4] | (body[5] << 8)) / 8.0 - 256.0
    return distance, strength, temp_c


try:
    while True:
        port.reset_input_buffer()       # drop old frames so the reading is fresh
        reading = read_frame()
        while reading is None:
            reading = read_frame()
        distance, strength, temp_c = reading
        if strength < 100 or strength == 65535:
            print("Signal unreliable - target too far, too dark, or overexposed")
        else:
            print(f"Distance: {distance} cm   Strength: {strength}   Chip temp: {temp_c:.1f} C")
        time.sleep(0.1)
except KeyboardInterrupt:
    port.close()
