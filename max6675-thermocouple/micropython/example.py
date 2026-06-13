# Reads temperature from a MAX6675 using MicroPython on a Pico (or similar) via SPI, converting the raw 12-bit value to Celsius and printing the result while detecting an open thermocouple.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max6675-module-k-type-thermocouple-sensor-measures-up-to-1024-degrees-manual
# More examples: https://github.com/shillehtek/examples
#

# MAX6675 K-type thermocouple - Pico (MicroPython)
# SPI0: SCK=GP18, MISO=GP16, CS=GP17

from machine import Pin, SPI
import time

spi = SPI(0, baudrate=1000000, polarity=0, phase=0,
          sck=Pin(18), mosi=Pin(19), miso=Pin(16))
cs = Pin(17, Pin.OUT, value=1)

def read_temp_c():
    cs.value(0)
    raw = spi.read(2)
    cs.value(1)
    value = (raw[0] << 8) | raw[1]

    if value & 0x4:
        return None
    return (value >> 3) * 0.25

while True:
    c = read_temp_c()
    if c is None:
        print("Thermocouple disconnected!")
    else:
        print("Temp: {:.2f} C".format(c))
    time.sleep(0.3)
