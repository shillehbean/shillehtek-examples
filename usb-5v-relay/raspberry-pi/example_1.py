# Minimal Linux command-line (bash) script that sets the serial port parameters and writes the 4-byte ON or OFF sequence to a USB serial device for quick on/off control.
#
# Buy this module: https://shillehtek.com/products/usb-control-module-1-channel-5v-relay-module-no-driver-needed
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/usb-control-module-1-channel-5v-relay-module-no-driver-needed-manual
# More examples: https://github.com/shillehtek/examples
#

#!/bin/bash
# Quick command-line relay control
# Usage: ./usb_relay.sh on   or   ./usb_relay.sh off

PORT="/dev/ttyUSB0"
stty -F "$PORT" 9600 raw -echo

if [ "$1" = "on" ]; then
  printf '\xA0\x01\x01\xA2' > "$PORT"
  echo "Relay ON"
elif [ "$1" = "off" ]; then
  printf '\xA0\x01\x00\xA1' > "$PORT"
  echo "Relay OFF"
else
  echo "Usage: $0 on|off"
fi
