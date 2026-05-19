# MicroPython example for the Pico that uses a micropython-max30102 driver over SoftI2C to read red and IR samples and print values when a finger is detected.
#
# Buy this module: https://shillehtek.com/products/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# MAX30102 Heart Rate Sensor - Pico MicroPython Example
# Install library: import mip; mip.install("github:n-undertaker/micropython-max30102")
# I2C Pins: GP0 (SDA), GP1 (SCL)

from machine import Pin, I2C, SoftI2C
from max30102 import MAX30102
import time

# Initialize I2C bus
i2c = SoftI2C(sda=Pin(0), scl=Pin(1), freq=400000)

# Scan for devices to verify connection
devices = i2c.scan()
print("I2C devices found:", [hex(d) for d in devices])

# Initialize the MAX30102 sensor
sensor = MAX30102(i2c=i2c)

# Check sensor is responding
if sensor.i2c_address not in devices:
    print("MAX30102 not found. Check wiring.")
    raise SystemExit

# Configure the sensor
sensor.setup_sensor()

print("MAX30102 Heart Rate Sensor")
print("Place your finger on the sensor...")

while True:
    # Check if new data is available
    sensor.check()

    if sensor.available():
        # Read red and IR values
        red = sensor.pop_red_from_storage()
        ir = sensor.pop_ir_from_storage()

        if ir < 50000:
            print("No finger detected")
        else:
            print("IR: {}, Red: {}".format(ir, red))

    time.sleep_ms(10)
