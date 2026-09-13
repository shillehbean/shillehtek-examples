# Create a Mosquitto password file and add a user account (examples for macOS, Linux, and Windows paths).
#
# Full tutorial: https://shillehtek.com/blogs/news/esp32-espresense-aws-iot-integration
# Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# macOS (Homebrew)
mosquitto_passwd -c /opt/homebrew/etc/mosquitto/password_file Username

# Linux
sudo mosquitto_passwd -c /etc/mosquitto/password_file Username

# Windows (run as Administrator)
mosquitto_passwd -c "C:\Program Files\Mosquitto\password_file" Username
