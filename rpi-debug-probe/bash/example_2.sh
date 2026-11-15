# Installs minicom and opens the probe UART at 115200 baud; replace /dev/ttyACM0 if the system assigns a different device.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-debug-probe-swd-uart-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-debug-probe-swd-uart-kit-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Open the probe's UART at 115200 baud
# The port name can differ - list the candidates with: ls /dev/ttyACM*
sudo apt install minicom
minicom -b 115200 -o -D /dev/ttyACM0
