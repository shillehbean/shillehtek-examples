# Install git/curl, clone the Zigbee2MQTT repository to /opt/zigbee2mqtt, and change into that directory.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-zigbee-dongle-plus-e-zigbee2mqtt
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt install -y git curl
sudo git clone https://github.com/Koenkk/zigbee2mqtt.git /opt/zigbee2mqtt
cd /opt/zigbee2mqtt
