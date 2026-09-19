# Linux/flashrom workflow: install flashrom, probe the CH341A, read the flash twice and compare hashes, write a new firmware image (flashrom erases and verifies), and explicitly verify a file when needed.
#
# Buy this module: https://shillehtek.com/products/ch341a-usb-eeprom-bios-programmer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ch341a-usb-eeprom-bios-programmer-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Install and probe
sudo apt update
sudo apt install flashrom
sudo flashrom -p ch341a_spi

# Read the flash TWICE and make sure the dumps match
sudo flashrom -p ch341a_spi -r backup1.bin
sudo flashrom -p ch341a_spi -r backup2.bin
md5sum backup1.bin backup2.bin

# Write a new image (flashrom erases and verifies automatically)
sudo flashrom -p ch341a_spi -w firmware.bin

# Explicit verify against a file, any time
sudo flashrom -p ch341a_spi -v firmware.bin
