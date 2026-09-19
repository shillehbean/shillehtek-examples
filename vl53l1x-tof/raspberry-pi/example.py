# Uses the vl53l1x Python package on a Raspberry Pi to open the sensor, start long-range ranging, and print distance readings every 0.1 seconds until interrupted.
#
# Buy this module: https://shillehtek.com/products/vl53l1x-tof-sensor-4m-pre-soldered-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vl53l1x-tof-sensor-4m-pre-soldered-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import VL53L1X

# pip3 install vl53l1x

tof = VL53L1X.VL53L1X(i2c_bus=1, i2c_address=0x29)
tof.open()
tof.start_ranging(3)   # 1=short, 2=medium, 3=long

try:
    while True:
        mm = tof.get_distance()
        print(f"Distance: {mm} mm ({mm / 10:.1f} cm)")
        time.sleep(0.1)
except KeyboardInterrupt:
    tof.stop_ranging()
