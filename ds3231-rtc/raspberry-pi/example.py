# Uses Adafruit CircuitPython DS3231 driver on a Raspberry Pi to print the current date/time and temperature every second, with a commented section to set the RTC once.
#
# Buy this module: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install adafruit-circuitpython-ds3231
# Enable I2C: sudo raspi-config

import time
import board, busio
import adafruit_ds3231

i2c = busio.I2C(board.SCL, board.SDA)
rtc = adafruit_ds3231.DS3231(i2c)

# Set time once (uncomment, run, then re-comment):
# t = time.struct_time((2026, 5, 3, 12, 0, 0, 0, -1, -1))
# rtc.datetime = t

while True:
    t = rtc.datetime
    print(f"{t.tm_year}-{t.tm_mon:02d}-{t.tm_mday:02d} "
          f"{t.tm_hour:02d}:{t.tm_min:02d}:{t.tm_sec:02d}")
    print(f"Temp: {rtc.temperature:.2f} C")
    time.sleep(1)
