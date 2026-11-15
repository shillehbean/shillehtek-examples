# On a Raspberry Pi, use adafruit-circuitpython-bno08x over I2C to enable the game rotation vector and convert the quaternion to yaw/pitch/roll for printing.
#
# Buy this module: https://shillehtek.com/products/bno085-imu-pre-soldered-orientation-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bno085-imu-pre-soldered-orientation-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# BNO085 (GY-BNO08X) on Raspberry Pi over I2C
# Install once: pip3 install adafruit-circuitpython-bno08x   (enable I2C in raspi-config)
# Recommended: add dtparam=i2c_arm_baudrate=400000 to /boot/firmware/config.txt, then reboot
import math
import time
import board
import busio
from adafruit_bno08x import BNO_REPORT_GAME_ROTATION_VECTOR
from adafruit_bno08x.i2c import BNO08X_I2C

i2c = busio.I2C(board.SCL, board.SDA, frequency=400000)
bno = BNO08X_I2C(i2c, address=0x4B)      # use 0x4A if ADD is tied to GND
bno.enable_feature(BNO_REPORT_GAME_ROTATION_VECTOR)

while True:
    qi, qj, qk, qr = bno.game_quaternion
    yaw = math.degrees(math.atan2(2 * (qi * qj + qk * qr), 1 - 2 * (qj * qj + qk * qk)))
    pitch = math.degrees(math.asin(max(-1.0, min(1.0, 2 * (qj * qr - qi * qk)))))
    roll = math.degrees(math.atan2(2 * (qj * qk + qi * qr), 1 - 2 * (qi * qi + qj * qj)))
    print(f"Yaw: {yaw:7.1f}   Pitch: {pitch:6.1f}   Roll: {roll:7.1f}")
    time.sleep(0.1)
