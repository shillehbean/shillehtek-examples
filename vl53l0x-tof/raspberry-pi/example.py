# Runs on a Raspberry Pi with Adafruit CircuitPython to read the VL53L0X range in a loop and optionally increase the measurement timing budget for higher accuracy.
#
# Buy this module: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-vl53l0xv2-laser-ranging-tof-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

# VL53L0X on Raspberry Pi using Adafruit CircuitPython
# Install: pip install adafruit-circuitpython-vl53l0x --break-system-packages

import time
import board
import busio
import adafruit_vl53l0x

i2c = busio.I2C(board.SCL, board.SDA)
sensor = adafruit_vl53l0x.VL53L0X(i2c)

# Optional: extend timing budget for more accuracy (default 33000 us)
sensor.measurement_timing_budget = 200000  # 200 ms

print("VL53L0X ready. Reading distance...")
while True:
    try:
        distance = sensor.range
        print(f"Distance: {distance} mm")
        time.sleep(0.1)
    except KeyboardInterrupt:
        break
