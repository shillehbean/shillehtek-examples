# I2C EEPROM tools: GUI route using imsprog on Debian/Ubuntu/Raspberry Pi OS to read/write 24Cxx parts, and CLI route using the ch341eeprom utility to read and write 24C64 chips.
#
# Buy this module: https://shillehtek.com/products/ch341a-usb-eeprom-bios-programmer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ch341a-usb-eeprom-bios-programmer-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# GUI route (Debian 12+ / Ubuntu 24.04+ / recent Raspberry Pi OS)
sudo apt install imsprog
imsprog   # pick the 24Cxx part, then Read / Write / Verify

# CLI route: the open-source ch341eeprom tool
# (build it from its GitHub repo if your distro has no package)
sudo ch341eeprom -s 24c64 -r dump.bin    # read a 24C64
sudo ch341eeprom -s 24c64 -w dump.bin    # write it back
