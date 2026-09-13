# Create and activate a Python virtual environment and install the Meshtastic CLI/package.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-sx1262-offline-mesh-messaging
# Parts used: https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino
#             https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

python3 -m venv meshtastic-env
source meshtastic-env/bin/activate
pip install -U meshtastic
