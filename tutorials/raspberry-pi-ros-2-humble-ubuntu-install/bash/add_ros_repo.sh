# Add the ROS 2 Humble apt repository to the system's sources.list so packages can be installed from packages.ros.org.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ros-2-humble-ubuntu-install
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

echo "deb [arch=arm64 signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu jammy main" | \
sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
