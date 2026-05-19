# Raspberry Pi Python example that reads sequential red and IR samples from the MAX30102, detects whether a finger is present, and prints averaged red/IR values.
#
# Buy this module: https://shillehtek.com/products/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# MAX30102 Heart Rate Sensor - Raspberry Pi Example
# Install: pip3 install max30102 smbus2
# I2C Pins: GPIO 2 (SDA), GPIO 3 (SCL)
# Enable I2C first: sudo raspi-config -> Interface Options -> I2C

from max30102 import MAX30102
import time

# Initialize the sensor on I2C bus 1
sensor = MAX30102(bus=1)

# Check if sensor is connected
if not sensor.check():
    print("MAX30102 not found. Check wiring.")
    exit(1)

print("MAX30102 Heart Rate Sensor")
print("Place your finger on the sensor...")
print("Press Ctrl+C to stop")

try:
    while True:
        # Read a batch of samples from the sensor
        red, ir = sensor.read_sequential()

        if len(ir) > 0:
            # Calculate average IR value (used for finger detection)
            avg_ir = sum(ir) / len(ir)

            if avg_ir < 50000:
                print("No finger detected")
            else:
                print("IR: {:.0f}, Red: {:.0f}".format(
                    sum(ir) / len(ir),
                    sum(red) / len(red)
                ))

        time.sleep(0.1)

except KeyboardInterrupt:
    print("\nMeasurement stopped by user")
finally:
    sensor.shutdown()
