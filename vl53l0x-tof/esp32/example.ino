// ESP32 MicroPython example that scans I2C, starts the VL53L0X using the vl53l0x driver, and prints continuous distance measurements.
//
// Buy this module: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-vl53l0xv2-laser-ranging-tof-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

# VL53L0X on ESP32 (MicroPython)
# Wiring: VCC->3V3, GND->GND, SCL->GPIO22, SDA->GPIO21
# Upload vl53l0x.py driver to the board first (same driver as Pico).

from machine import I2C, Pin
from vl53l0x import VL53L0X
import time

i2c = I2C(0, scl=Pin(22), sda=Pin(21), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])

tof = VL53L0X(i2c)
tof.start()

while True:
    print("Distance:", tof.read(), "mm")
    time.sleep_ms(100)
