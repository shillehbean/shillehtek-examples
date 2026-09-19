# On an ESP32 running MicroPython, scans I2C, wakes the MPU6050, reads raw sensor registers, scales accelerometer and gyroscope values to physical units, and prints the results continuously.
#
# Buy this module: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu6050-accelerometer-6dof-raspberry-pi-arduino-esp32-i2c-accelerometer
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MPU6050 IMU - ESP32 MicroPython Example
# I2C: SDA -> GPIO 21, SCL -> GPIO 22

from machine import I2C, Pin
import time, struct

MPU_ADDR  = 0x68
PWR_MGMT  = 0x6B
ACCEL_OUT = 0x3B

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=400000)

print("I2C devices:", [hex(d) for d in i2c.scan()])

# Wake up the sensor
i2c.writeto_mem(MPU_ADDR, PWR_MGMT, b'\x00')

while True:
    raw = i2c.readfrom_mem(MPU_ADDR, ACCEL_OUT, 14)
    ax, ay, az, t, gx, gy, gz = struct.unpack('>hhhhhhh', raw)
    print("Accel g: {:+.2f} {:+.2f} {:+.2f}   Gyro d/s: {:+.1f} {:+.1f} {:+.1f}".format(
        ax/16384.0, ay/16384.0, az/16384.0,
        gx/131.0,   gy/131.0,   gz/131.0))
    time.sleep_ms(500)
