# Commands for an existing ESP-IDF project: select esp32p4, build, and flash with a serial monitor after replacing PORT with the actual serial port.
#
# Buy this module: https://shillehtek.com/products/esp32-p4-wifi-6-development-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-p4-wifi-6-development-kit-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Run inside an ESP-IDF project folder (ESP-IDF 5.3.1 or newer)
idf.py set-target esp32p4
idf.py build
# Replace PORT with the board's serial port, for example /dev/ttyACM0 or COM5
idf.py -p PORT flash monitor
