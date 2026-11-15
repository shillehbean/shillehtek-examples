# MicroPython script for a Raspberry Pi Pico that reads TF-Luna frames from UART(1), validates and decodes them, and keeps the latest valid reading by draining the UART buffer.
#
# Buy this module: https://shillehtek.com/products/lidar-tf-luna-single-module-8m
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lidar-tf-luna-single-module-8m-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TF-Luna LiDAR on Raspberry Pi Pico (MicroPython) over UART1
# TF-Luna TXD (pin 3) -> GP5 (Pico RX), RXD (pin 2) -> GP4 (Pico TX), +5V -> VBUS, GND -> GND
from machine import UART, Pin
import time

uart = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5))


def read_frame():
    """Return (distance_cm, strength, temp_c), or None if no valid frame is waiting."""
    while uart.any() >= 9:
        if uart.read(1) != b"Y":        # 0x59, first header byte
            continue
        if uart.read(1) != b"Y":        # 0x59, second header byte
            continue
        body = uart.read(7)
        if body is None or len(body) != 7:
            return None
        if (0x59 + 0x59 + sum(body[:6])) & 0xFF != body[6]:
            continue                    # checksum mismatch
        distance = body[0] | (body[1] << 8)
        strength = body[2] | (body[3] << 8)
        temp_c = (body[4] | (body[5] << 8)) / 8 - 256
        return distance, strength, temp_c
    return None


while True:
    latest = None
    reading = read_frame()
    while reading:                      # drain the buffer and keep the newest frame
        latest = reading
        reading = read_frame()
    if latest:
        distance, strength, temp_c = latest
        if strength < 100 or strength == 65535:
            print("Signal unreliable - target too far, too dark, or overexposed")
        else:
            print("Distance: {} cm   Strength: {}   Chip temp: {:.1f} C".format(distance, strength, temp_c))
    time.sleep(0.1)
