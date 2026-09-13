# Stop or disable the Mosquitto service on macOS, Linux, and Windows.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-espresense-aws-iot-integration
# Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Stop on macOS
brew services stop mosquitto

# Stop on Linux
sudo systemctl stop mosquitto
sudo systemctl disable mosquitto

# Stop on Windows (run as Administrator)
net stop mosquitto
