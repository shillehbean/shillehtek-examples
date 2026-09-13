# Installs the system I2C support and the Python mpu6050-raspberrypi library required to read data from the MPU6050 on a Raspberry Pi.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-4-mpu6050-python-readings
# Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
#             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt install python3-smbus

pip install mpu6050-raspberrypi
