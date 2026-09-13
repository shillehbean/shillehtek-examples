# Add the NodeSource Node.js 18 setup script and install Node.js on the Raspberry Pi.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-zigbee-dongle-plus-e-zigbee2mqtt
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
