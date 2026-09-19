# Performs low-level I2C register reads/writes on a Raspberry Pi Pico running MicroPython to enable the proximity engine and continuously read raw proximity values from the APDS-9960.
#
# Buy this module: https://shillehtek.com/products/apds-9960-gesture-proximity-color-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/apds-9960-gesture-proximity-color-sensor-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# APDS-9960 Proximity Reading - Raspberry Pi Pico MicroPython Example
# SDA: GP0, SCL: GP1 (I2C0), VCC: 3V3 OUT (pin 36)
# No external library needed - reads the sensor registers directly.

from machine import Pin, I2C
import time

APDS_ADDR  = 0x39   # Fixed I2C address of the APDS-9960
REG_ENABLE = 0x80   # Power / feature enable register
REG_PPULSE = 0x8E   # Proximity IR pulse configuration
REG_ID     = 0x92   # Device ID register
REG_PDATA  = 0x9C   # Proximity data register

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)

# Sanity check: the sensor should answer at 0x39
if APDS_ADDR not in i2c.scan():
    raise RuntimeError("APDS-9960 not found at 0x39 - check wiring")

chip_id = i2c.readfrom_mem(APDS_ADDR, REG_ID, 1)[0]
print("Device ID: 0x{:02X}".format(chip_id))

# 8 IR pulses of 16 us each (same default the SparkFun library uses)
i2c.writeto_mem(APDS_ADDR, REG_PPULSE, b'\x87')

# ENABLE register: PON (bit 0) powers the chip, PEN (bit 2)
# starts the proximity engine -> 0b00000101 = 0x05
i2c.writeto_mem(APDS_ADDR, REG_ENABLE, b'\x05')
time.sleep_ms(10)

while True:
    # PDATA: 0 (nothing in range) up to 255 (object right at the lens)
    prox = i2c.readfrom_mem(APDS_ADDR, REG_PDATA, 1)[0]
    print("Proximity:", prox)
    time.sleep_ms(200)
