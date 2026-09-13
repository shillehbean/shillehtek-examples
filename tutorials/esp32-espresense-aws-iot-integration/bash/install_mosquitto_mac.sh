# Install Mosquitto via Homebrew and start the service on macOS.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-espresense-aws-iot-integration
# Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

brew install mosquitto
brew services start mosquitto
