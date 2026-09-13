# Point a secondary node at the primary channel URL, set the LoRa region, and reboot the secondary node so it joins the network.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-sx1262-offline-mesh-messaging
# Parts used: https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino
#             https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

meshtastic --port /dev/cu.usbserial-0002 --ch-set-url "https://meshtastic.org/e/#..."
meshtastic --port /dev/cu.usbserial-0002 --set lora.region US
meshtastic --port /dev/cu.usbserial-0002 --reboot
