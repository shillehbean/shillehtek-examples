# Raspberry Pi flashrom example: install flashrom on Raspberry Pi OS, read a connected SPI flash with the CH341A and compute a checksum, plus an optional udev rule to allow non-root access to the device.
#
# Buy this module: https://shillehtek.com/products/ch341a-usb-eeprom-bios-programmer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ch341a-usb-eeprom-bios-programmer-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Same flashrom workflow, on Raspberry Pi OS
sudo apt update
sudo apt install flashrom

# Plug the CH341A into any USB port, then:
sudo flashrom -p ch341a_spi -r router_backup.bin
sha256sum router_backup.bin

# Optional: allow running without sudo
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="5512", MODE="0666"' | sudo tee /etc/udev/rules.d/99-ch341a.rules
sudo udevadm control --reload-rules
