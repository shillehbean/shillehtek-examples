// Use esptool via the FT232RL to detect the ESP-01, erase flash, and write a new firmware image to an ESP8266-based module.
//
// Buy this module: https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs-manual
// More examples: https://github.com/shillehtek/examples
//

# Flash a firmware image to an ESP-01 / ESP8266 via the FT232RL.
# Requires: pip install esptool
# Hold GPIO0 to GND while powering on the ESP-01 to enter flash mode.

# 1. Verify the ESP8266 is responding
esptool.py --port /dev/ttyUSB0 --baud 115200 chip_id

# 2. Erase existing flash (optional but recommended)
esptool.py --port /dev/ttyUSB0 --baud 115200 erase_flash

# 3. Write new firmware (replace path with your .bin file)
esptool.py --port /dev/ttyUSB0 --baud 115200 write_flash 0x00000 firmware.bin

# After flashing: disconnect GPIO0 from GND and reset the ESP-01 to run.
