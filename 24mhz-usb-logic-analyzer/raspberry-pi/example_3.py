# A sigrok-cli command to capture 5 seconds of I2C from channels D0/D1 at 8 MS/s and save the recording as a PulseView-compatible .sr file.
#
# Buy this module: https://shillehtek.com/products/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/bin/bash
# Capture 5 seconds of an I2C bus on CH0 (SDA) and CH1 (SCL)
# Output as a .sr file you can open in PulseView later

sigrok-cli --driver fx2lafw --config samplerate=8m \
  --channels D0,D1 --time 5000 --output-format srzip \
  --output-file i2c_capture.sr
