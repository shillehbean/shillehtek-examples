# Send a 433 MHz code from a Raspberry Pi GPIO pin using the rpi-rf library to trigger the relay's receiver (useful after learning the remote code).
#
# Buy this module: https://shillehtek.com/products/433mhz-12v-1-channel-relay-module-with-wireless-remote
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/433mhz-12v-1-channel-relay-module-with-wireless-remote-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install rpi-rf
# TX module DATA -> GPIO 17 (Pin 11)

from rpi_rf import RFDevice
import time

tx = RFDevice(17)
tx.enable_tx()

# Replace with your remote's actual code (use receive script first)
tx.tx_code(1234567, 1, 350)
time.sleep(1)
tx.cleanup()
