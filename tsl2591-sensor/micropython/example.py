# Uses low-level I2C register access in MicroPython on a Pico to read full-spectrum and infrared channels and calculate illuminance in lux.
#
# Buy this module: https://shillehtek.com/products/tsl2591-light-sensor-presoldered-purple-breakout-single
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tsl2591-light-sensor-presoldered-purple-breakout-single-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TSL2591 light sensor on Raspberry Pi Pico (MicroPython, no driver file needed)
# SDA = GP4 (pin 6), SCL = GP5 (pin 7), VIN = 3V3(OUT), GND = GND
from machine import I2C, Pin
import time

ADDR = 0x29
CMD = 0xA0            # command bit for normal register access
REG_ENABLE = 0x00
REG_CONTROL = 0x01
REG_ID = 0x12         # reads 0x50 on a TSL2591
REG_CH0_LOW = 0x14    # full spectrum, 2 bytes, low byte first
REG_CH1_LOW = 0x16    # infrared, 2 bytes, low byte first

GAIN = 0x10           # 0x00 = 1x, 0x10 = 25x, 0x20 = 428x, 0x30 = 9876x
GAIN_FACTOR = 25.0
TIME = 0x02           # 0x00 to 0x05 = 100 to 600 ms
TIME_MS = 300.0

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)

if i2c.readfrom_mem(ADDR, CMD | REG_ID, 1)[0] != 0x50:
    raise RuntimeError("TSL2591 not found - check wiring")

i2c.writeto_mem(ADDR, CMD | REG_CONTROL, bytes([GAIN | TIME]))
i2c.writeto_mem(ADDR, CMD | REG_ENABLE, bytes([0x03]))     # power on + enable the ADC


def read_channels():
    time.sleep_ms(int(TIME_MS) + 120)                      # wait for one full integration
    ch0 = int.from_bytes(i2c.readfrom_mem(ADDR, CMD | REG_CH0_LOW, 2), "little")
    ch1 = int.from_bytes(i2c.readfrom_mem(ADDR, CMD | REG_CH1_LOW, 2), "little")
    return ch0, ch1


def to_lux(ch0, ch1):
    if ch0 == 0xFFFF or ch1 == 0xFFFF:
        return None                                        # saturated: lower the gain
    if ch0 == 0:
        return 0.0
    cpl = (TIME_MS * GAIN_FACTOR) / 408.0                  # counts per lux
    return (ch0 - ch1) * (1.0 - ch1 / ch0) / cpl


while True:
    full, ir = read_channels()
    lux = to_lux(full, ir)
    if lux is None:
        print("Overflow - lower the gain")
    else:
        print("Lux: {:.2f}   Full: {}   IR: {}".format(lux, full, ir))
    time.sleep(1)
