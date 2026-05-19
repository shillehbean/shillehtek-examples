# Shows how to locate the CP2102 serial device on Linux/macOS and open a serial console at 115200 baud using the screen utility (including how to quit).
#
# Buy this module: https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# Linux: device shows up as /dev/ttyUSB0 (or USB1, USB2...)
ls -l /dev/ttyUSB*
sudo screen /dev/ttyUSB0 115200

# macOS: device shows up as /dev/cu.SLAB_USBtoUART
ls -l /dev/cu.*
screen /dev/cu.SLAB_USBtoUART 115200

# Quit screen with: Ctrl-A, then K, then Y
