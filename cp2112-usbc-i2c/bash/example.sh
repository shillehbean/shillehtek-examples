# Interactive Linux setup: install i2c-tools, load the CP2112 drivers, list I2C buses, and replace example bus 8 with the actual adapter bus before scanning.
#
# Buy this module: https://shillehtek.com/products/cp2112-usbc-i2c-smbus-adapter-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cp2112-usbc-i2c-smbus-adapter-presoldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 1. Install the I2C tools and load the kernel drivers
sudo apt install i2c-tools
sudo modprobe hid-cp2112
sudo modprobe i2c-dev

# 2. Find the bus the adapter created (look for "CP2112 SMBus Bridge")
i2cdetect -l

# 3. Scan that bus - replace 8 with your bus number
sudo i2cdetect -y -r 8
