# Apply a channel URL to a device, set the LoRa region, and reboot the node.
#
# Full tutorial: https://shillehtek.com/blogs/news/meshtastic-bme280-lora-environment-telemetry-esp32-sx1262
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

meshtastic --port /dev/cu.usbserial-3 --ch-set-url "https://meshtastic.org/e/#..."
meshtastic --port /dev/cu.usbserial-3 --set lora.region US
meshtastic --port /dev/cu.usbserial-3 --reboot
