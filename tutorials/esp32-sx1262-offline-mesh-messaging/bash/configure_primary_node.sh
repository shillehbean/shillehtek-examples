# Open channel editing on a device and configure the primary channel name, a random pre-shared key, and the LoRa region, then commit the changes.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-sx1262-offline-mesh-messaging
# Parts used: https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino
#             https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

meshtastic --port /dev/cu.usbserial-0001 --begin-edit
meshtastic --port /dev/cu.usbserial-0001 --ch-index 0 --ch-set name shillehtek
meshtastic --port /dev/cu.usbserial-0001 --ch-index 0 --ch-set psk random
meshtastic --port /dev/cu.usbserial-0001 --set lora.region US
meshtastic --port /dev/cu.usbserial-0001 --commit-edit
