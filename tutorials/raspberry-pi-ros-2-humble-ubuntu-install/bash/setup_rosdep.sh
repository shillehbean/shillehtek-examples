# Install and initialize rosdep, then update its database so system dependencies for ROS packages can be installed automatically.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ros-2-humble-ubuntu-install
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

sudo apt install python3-rosdep
sudo rosdep init
rosdep update
