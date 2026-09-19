# Uses smbus2 and the mlx90614 Python package on a Raspberry Pi to read ambient and object temperatures over I2C and print them once per second.
#
# Buy this module: https://shillehtek.com/products/pre-soldered-gy-906-mlx90614-baa-infrared-temperature-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-906-mlx90614-baa-non-touch-infrared-temperature-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MLX90614 on Raspberry Pi via I2C
# Install: pip install smbus2 mlx90614
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

from smbus2 import SMBus
from mlx90614 import MLX90614
import time

bus = SMBus(1)
sensor = MLX90614(bus, address=0x5A)

try:
    while True:
        print(f"Ambient: {sensor.get_ambient():.2f} C")
        print(f"Object:  {sensor.get_object_1():.2f} C")
        print("-" * 30)
        time.sleep(1)
except KeyboardInterrupt:
    bus.close()
