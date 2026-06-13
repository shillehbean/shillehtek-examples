# Uses an MCP3008 over SPI to read the sensor on CH0, clamps and scales the Adafruit library 0–65535 ADC value into a 0–100% moisture percentage, and prints raw, voltage, and percent values in a loop.
#
# Buy this module: https://shillehtek.com/products/Analog
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/capacitive-soil-moisture-sensor-v1-2-manual
# More examples: https://github.com/shillehtek/examples
#

# Capacitive Soil Moisture Sensor V1.2 - Raspberry Pi
# Requires an MCP3008 ADC over SPI.
# pip install adafruit-circuitpython-mcp3xxx

import time
import board
import busio
import digitalio
from adafruit_mcp3xxx.mcp3008 import MCP3008
from adafruit_mcp3xxx.analog_in import AnalogIn

spi = busio.SPI(clock=board.SCK, MISO=board.MISO, MOSI=board.MOSI)
cs = digitalio.DigitalInOut(board.D8)
mcp = MCP3008(spi, cs)
chan = AnalogIn(mcp, 0)  # MCP3008 CH0

# Calibrate (0-65535 scale from adafruit lib)
DRY_VALUE = 48000
WET_VALUE = 20000

while True:
    raw = chan.value
    clamped = max(WET_VALUE, min(DRY_VALUE, raw))
    percent = int((DRY_VALUE - clamped) * 100 / (DRY_VALUE - WET_VALUE))
    print(f"Raw: {raw}  Voltage: {chan.voltage:.2f}V  Moisture: {percent}%")
    time.sleep(1)
