# Install and enable the Mosquitto MQTT broker on the Raspberry Pi.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-zigbee-dongle-plus-e-zigbee2mqtt
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt update
sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto
