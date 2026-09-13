# Update package lists, install pip3, and install the Adafruit ADS1x15 Python library.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ads1115-read-mq135-voltage
# Parts used: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
#             https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt-get update
sudo apt-get install python3-pip
sudo pip3 install adafruit-ads1x15
