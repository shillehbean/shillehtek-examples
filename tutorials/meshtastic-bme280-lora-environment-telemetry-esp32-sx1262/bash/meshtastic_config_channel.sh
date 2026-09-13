# Begin editing the device config, set the primary channel name and PSK, set the LoRa region, and commit the changes.
#
# Full tutorial: https://shillehtek.com/blogs/news/meshtastic-bme280-lora-environment-telemetry-esp32-sx1262
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

meshtastic --port /dev/cu.usbserial-0001 --begin-edit
meshtastic --port /dev/cu.usbserial-0001 --ch-index 0 --ch-set name shillehtek
meshtastic --port /dev/cu.usbserial-0001 --ch-index 0 --ch-set psk random
meshtastic --port /dev/cu.usbserial-0001 --set lora.region US
meshtastic --port /dev/cu.usbserial-0001 --commit-edit
