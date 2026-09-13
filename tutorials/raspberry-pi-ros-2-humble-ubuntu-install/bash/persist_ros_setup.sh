# Append the ROS 2 Humble setup script to ~/.bashrc so the ROS environment is loaded on each new shell, then source the updated bashrc.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ros-2-humble-ubuntu-install
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc
