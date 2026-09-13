# Installs system packages and Python libraries (smbus2 and mpu9250-jmdev) required to run the Raspberry Pi MPU9250 example.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-mpu9250-read-9-axis-data
# Parts used: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt-get update
sudo apt-get install python3-pip
sudo pip3 install smbus2
sudo pip3 install mpu9250-jmdev
