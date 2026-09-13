# Install the urequests HTTP library on the ESP32 MicroPython runtime using upip.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-cam-camera-micropython-wifi-setup
# Parts used: https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino
#             https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import upip
upip.install("urequests")
