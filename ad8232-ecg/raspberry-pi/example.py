# Uses an MCP3008 over SPI to read the AD8232 ECG output on a Raspberry Pi, checks LO+ and LO- GPIOs for leads-off, and prints samples at ~200 Hz.
#
# Buy this module: https://shillehtek.com/products/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# AD8232 ECG Module - Raspberry Pi Example (via MCP3008 ADC)
# Install: pip3 install spidev gpiozero
# AD8232 OUTPUT -> MCP3008 CH0
# LO+ -> GPIO 27, LO- -> GPIO 17

import spidev
import time
from gpiozero import DigitalInputDevice

LO_PLUS  = DigitalInputDevice(27)
LO_MINUS = DigitalInputDevice(17)

spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 1_350_000

def read_adc(channel):
    # MCP3008 single-ended read
    r = spi.xfer2([1, (8 + channel) << 4, 0])
    return ((r[1] & 3) << 8) | r[2]

print("AD8232 ECG Demo (Ctrl+C to stop)")

try:
    while True:
        if LO_PLUS.value or LO_MINUS.value:
            print(0)              # leads off
        else:
            ecg = read_adc(0)     # 0 - 1023
            print(ecg)
        time.sleep(0.005)         # ~200 Hz
except KeyboardInterrupt:
    print("\nStopped by user")
finally:
    spi.close()
