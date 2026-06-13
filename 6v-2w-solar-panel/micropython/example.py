# Talks to an INA219 over I2C from a Pico (MicroPython) to read bus voltage and shunt current, compute power, and print voltage/current/power values periodically.
#
# Buy this module: https://shillehtek.com/products/110-x-136mm-6v-2w-solar-panel
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/110-x-136mm-6v-2w-solar-panel-manual
# More examples: https://github.com/shillehtek/examples
#

# 6V 2W Panel + INA219 + Pico - measures voltage AND current.
# INA219 in series between panel + and charger VIN.
# I2C: SDA = GP0, SCL = GP1

from machine import I2C, Pin
import time

# Minimal INA219 driver (default 0x40 address)
INA219_ADDR = 0x40
REG_CONFIG = 0x00
REG_SHUNTV = 0x01
REG_BUSV = 0x02
REG_CALIB = 0x05

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)

def write16(reg, val):
    i2c.writeto_mem(INA219_ADDR, reg, bytes([val >> 8, val & 0xFF]))

def read16(reg):
    data = i2c.readfrom_mem(INA219_ADDR, reg, 2)
    return (data[0] << 8) | data[1]

# Configure for 16V range, 1A max, 0.1 ohm shunt
write16(REG_CONFIG, 0x199F)
write16(REG_CALIB, 4096)

CURRENT_LSB = 0.0001  # 100 uA per bit

while True:
    busv_raw = read16(REG_BUSV) >> 3
    v_bus = busv_raw * 0.004  # 4 mV per bit

    current_raw = read16(0x04)
    if current_raw > 32767:
        current_raw -= 65536
    i_ma = current_raw * CURRENT_LSB * 1000

    power_mw = v_bus * i_ma

    print("Panel: {:.2f} V  {:.0f} mA  {:.0f} mW".format(
        v_bus, i_ma, power_mw))

    time.sleep(2)
