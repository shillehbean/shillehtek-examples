# Performs raw I2C reads from the MPU6050 on a Raspberry Pi Pico running MicroPython, unpacks the sensor registers, scales accel/gyro/temperature to physical units, and prints them repeatedly.
#
# Buy this module: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu6050-accelerometer-6dof-raspberry-pi-arduino-esp32-i2c-accelerometer
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MPU6050 IMU - Pico MicroPython Example
# I2C0: SDA -> GP0, SCL -> GP1

from machine import I2C, Pin
import time, struct

MPU_ADDR  = 0x68
PWR_MGMT  = 0x6B
ACCEL_OUT = 0x3B

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)

# Wake up the sensor (clears sleep bit)
i2c.writeto_mem(MPU_ADDR, PWR_MGMT, b'\x00')

def read_all():
    raw = i2c.readfrom_mem(MPU_ADDR, ACCEL_OUT, 14)
    ax, ay, az, t, gx, gy, gz = struct.unpack('>hhhhhhh', raw)
    # Scale to physical units (default ranges: ±2g, ±250 deg/s)
    return {
        'ax': ax / 16384.0, 'ay': ay / 16384.0, 'az': az / 16384.0,
        'gx': gx / 131.0,   'gy': gy / 131.0,   'gz': gz / 131.0,
        'temp_c': t / 340.0 + 36.53
    }

print("MPU6050 IMU")
while True:
    d = read_all()
    print("Accel g: {ax:+.2f} {ay:+.2f} {az:+.2f}   Gyro d/s: {gx:+.1f} {gy:+.1f} {gz:+.1f}   T={temp_c:.1f}C"
          .format(**d))
    time.sleep_ms(500)
