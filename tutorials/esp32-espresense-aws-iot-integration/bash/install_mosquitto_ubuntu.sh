# Update apt package lists, install Mosquitto and its clients on Debian/Ubuntu, enable and start the Mosquitto systemd service.
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-espresense-aws-iot-integration
# Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt update
sudo apt install mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
