# Restart the Mosquitto service after configuration changes (commands for macOS, Linux, and Windows).
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-espresense-aws-iot-integration
# Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# macOS
brew services restart mosquitto

# Linux
sudo systemctl restart mosquitto

# Windows (run as Administrator)
net stop mosquitto
net start mosquitto
