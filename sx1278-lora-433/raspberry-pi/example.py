# Runs a Raspberry Pi receiver using the pyLoRa SX127x driver to print incoming payloads and RSSI in continuous RX mode.
#
# Buy this module: https://shillehtek.com/products/sx1278-lora-433mhz-transceiver-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1278-lora-433mhz-transceiver-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# Ra-02 SX1278 - Raspberry Pi LoRa receiver (pyLoRa)
# Install: pip3 install pyLoRa spidev RPi.GPIO
# Wiring: NSS->CE0, RESET->GPIO22, DIO0->GPIO24 (BOARD mode in lib config)

from SX127x.LoRa import LoRa
from SX127x.board_config import BOARD
import time

BOARD.setup()

class Receiver(LoRa):
    def __init__(self):
        super(Receiver, self).__init__(verbose=False)
        self.set_mode(0x80)          # sleep, LoRa mode
        self.set_freq(433.0)
        self.set_spreading_factor(9)
        self.set_bw(7)               # 7 = 125 kHz
        self.set_sync_word(0x12)
        self.set_rx_crc(True)

    def on_rx_done(self):
        payload = self.read_payload(nocheck=True)
        text = bytes(payload).decode(errors="ignore")
        print("Received: '{}'  RSSI: {} dBm".format(
            text, self.get_pkt_rssi_value()))
        self.set_mode(0x85)          # back to RX continuous

lora = Receiver()
print("LoRa receiver ready (433 MHz, SF9)")
lora.set_mode(0x85)                  # RX continuous

try:
    while True:
        time.sleep(0.5)
except KeyboardInterrupt:
    BOARD.teardown()
    print("Stopped by user")
