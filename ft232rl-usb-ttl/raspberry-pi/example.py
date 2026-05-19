# Locate the FT232RL serial device on Linux/macOS and open a serial console at 115200 baud using screen or minicom on a Raspberry Pi.
#
# Buy this module: https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs-manual
# More examples: https://github.com/shillehtek/examples
#

# Find the FT232RL port (Linux: /dev/ttyUSB*; macOS: /dev/tty.usbserial-*)
ls /dev/ttyUSB* 2>/dev/null
ls /dev/tty.usbserial-* 2>/dev/null

# Open a serial console at 115200 baud (common for Raspberry Pi)
# Linux/macOS: screen
screen /dev/ttyUSB0 115200

# Exit screen with: Ctrl+A then K, then Y to confirm.

# Alternative: minicom (Linux)
sudo apt install minicom
minicom -D /dev/ttyUSB0 -b 115200
