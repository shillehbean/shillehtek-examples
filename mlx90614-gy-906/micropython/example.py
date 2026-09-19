# Runs on a MicroPython board (e.g., Pico), uses I2C0 (GP0 SDA, GP1 SCL) with an mlx90614 driver to read and print ambient and object temperatures in a loop.
#
# Buy this module: https://shillehtek.com/products/pre-soldered-gy-906-mlx90614-baa-infrared-temperature-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-906-mlx90614-baa-non-touch-infrared-temperature-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MLX90614 on Pico via I2C0 (GP0 SDA, GP1 SCL)
# Upload an mlx90614.py driver to the Pico filesystem first.

from machine import I2C, Pin
from mlx90614 import MLX90614
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=100000)
print("I2C scan:", [hex(d) for d in i2c.scan()])

sensor = MLX90614(i2c)

while True:
    print("Ambient: {:.2f} C".format(sensor.read_ambient_temp()))
    print("Object:  {:.2f} C".format(sensor.read_object_temp()))
    print("-" * 30)
    time.sleep(1)
