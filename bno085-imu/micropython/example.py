# On a Raspberry Pi Pico running MicroPython, read 19‑byte UART RVC frames from the BNO085, verify the checksum and unpack yaw/pitch/roll and acceleration (converted to SI units).
#
# Buy this module: https://shillehtek.com/products/bno085-imu-pre-soldered-orientation-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bno085-imu-pre-soldered-orientation-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BNO085 (GY-BNO08X) on Raspberry Pi Pico in UART-RVC mode (MicroPython, no driver needed)
# Wiring: VCC -> 3V3(OUT), GND -> GND, PS0 -> 3V3(OUT), SDA pin (data out) -> GP5 (UART1 RX)
from machine import UART, Pin
import struct
import time

uart = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5), rxbuf=512)
HEADER = bytes([0xAA])


def read_frame():
    """Return ((yaw, pitch, roll) in degrees, (x, y, z) in m/s^2), or None."""
    while uart.any() >= 19:
        if uart.read(1) != HEADER:              # first header byte
            continue
        if uart.read(1) != HEADER:              # second header byte
            continue
        frame = uart.read(17)
        if frame is None or len(frame) != 17:
            return None
        if sum(frame[0:16]) & 0xFF != frame[16]:
            continue                            # checksum mismatch
        index, yaw, pitch, roll, ax, ay, az = struct.unpack_from("<Bhhhhhh", frame, 0)
        angles = (yaw * 0.01, pitch * 0.01, roll * 0.01)
        accel = (ax * 0.0098067, ay * 0.0098067, az * 0.0098067)    # mg to m/s^2
        return angles, accel
    return None


while True:
    latest = None
    reading = read_frame()
    while reading:                              # drain the buffer and keep the newest frame
        latest = reading
        reading = read_frame()
    if latest:
        (yaw, pitch, roll), (ax, ay, az) = latest
        print("Yaw: {:7.2f}  Pitch: {:6.2f}  Roll: {:7.2f}  Accel: {:5.2f} {:5.2f} {:5.2f}".format(
            yaw, pitch, roll, ax, ay, az))
    time.sleep(0.1)
