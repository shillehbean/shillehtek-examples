# Uses the mpu9250-jmdev Python package on a Raspberry Pi to configure the MPU9250 and periodically print accelerometer, gyroscope, and magnetometer readings via I2C.
#
# Buy this module: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu9250-authentic-gy-9250-pre-soldered-9-axis-9-dof-accelerometer-magnetometer
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MPU9250 on Raspberry Pi via I2C
# Install: pip install mpu9250-jmdev smbus2
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

import time
from mpu9250_jmdev.registers import AK8963_ADDRESS, GFS_1000, AFS_8G, AK8963_BIT_16, AK8963_MODE_C100HZ
from mpu9250_jmdev.mpu_9250 import MPU9250

mpu = MPU9250(
    address_ak=AK8963_ADDRESS,
    address_mpu_master=0x68,
    address_mpu_slave=None,
    bus=1,
    gfs=GFS_1000,
    afs=AFS_8G,
    mfs=AK8963_BIT_16,
    mode=AK8963_MODE_C100HZ)

mpu.configure()

while True:
    print("Accel:", mpu.readAccelerometerMaster())
    print("Gyro :", mpu.readGyroscopeMaster())
    print("Mag  :", mpu.readMagnetometerMaster())
    print("-" * 40)
    time.sleep(0.5)
