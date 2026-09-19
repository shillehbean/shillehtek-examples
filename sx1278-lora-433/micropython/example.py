# MicroPython example for a Pico that uses an sx127x driver to send periodic LoRa messages over SPI.
#
# Buy this module: https://shillehtek.com/products/sx1278-lora-433mhz-transceiver-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1278-lora-433mhz-transceiver-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Ra-02 SX1278 - Pico MicroPython sender
# Driver: copy sx127x.py from the micropython-lora project
#   (github.com/martynwheeler/u-lora or similar sx127x.py) to the Pico
# Wiring: SCK=GP2, MOSI=GP3, MISO=GP4, NSS=GP5, RESET=GP6, DIO0=GP7

from machine import Pin, SPI
from sx127x import SX127x
import time

lora_cfg = {
    "frequency": 433E6,
    "spreading_factor": 9,
    "signal_bandwidth": 125E3,
    "tx_power_level": 17,
    "sync_word": 0x12,
}

spi = SPI(0, baudrate=5_000_000,
          sck=Pin(2), mosi=Pin(3), miso=Pin(4))

lora = SX127x(spi,
              pins={"ss": 5, "reset": 6, "dio_0": 7},
              parameters=lora_cfg)

counter = 0
print("LoRa sender ready (433 MHz, SF9)")
while True:
    msg = "Pico #{}".format(counter)
    print("Sending:", msg)
    lora.println(msg)
    counter += 1
    time.sleep(2)
