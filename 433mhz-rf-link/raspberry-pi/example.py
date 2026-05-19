# Listens on GPIO27 with rpi-rf for raw 433 MHz codes and prints the received code, pulse length, and protocol information on a Raspberry Pi.
#
# Buy this module: https://shillehtek.com/products/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install rpi-rf
# RX DATA -> GPIO 27 (Pin 13)

from rpi_rf import RFDevice
import time

rx = RFDevice(27)
rx.enable_rx()
last_ts = 0

print("Listening for 433MHz codes...")
try:
    while True:
        if rx.rx_code_timestamp != last_ts:
            last_ts = rx.rx_code_timestamp
            print(f"Code: {rx.rx_code}  pulse: {rx.rx_pulselength}us "
                  f"protocol: {rx.rx_proto}")
        time.sleep(0.01)
except KeyboardInterrupt:
    rx.cleanup()
