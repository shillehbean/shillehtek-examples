# MicroPython example for a Pico or similar board: reads a digital input on Pin 15 and prints whether an obstacle is detected every 0.1 seconds.
#
# Buy this module: https://shillehtek.com/products/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot-manual
# More examples: https://github.com/shillehtek/examples
#

# IR Obstacle Sensor on Raspberry Pi Pico (MicroPython)

from machine import Pin
import time

sensor = Pin(15, Pin.IN)

while True:
    if sensor.value() == 0:
        print("Obstacle detected!")
    else:
        print("Path clear")
    time.sleep(0.1)
