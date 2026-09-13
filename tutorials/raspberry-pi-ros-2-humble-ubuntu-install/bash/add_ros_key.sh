# Download the ROS apt repository GPG key and save it to the system keyrings so apt can verify ROS packages.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ros-2-humble-ubuntu-install
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
