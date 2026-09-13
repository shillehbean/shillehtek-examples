# Installs the Mosquitto MQTT broker and clients via apt, and installs the paho-mqtt Python client via pip.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-mosquitto-mqtt-send-commands
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt update
sudo apt install -y mosquitto mosquitto-clients
pip install paho-mqtt
