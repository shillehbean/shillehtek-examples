# Creates a ROS 2 workspace and a new Python package 'bme280_reader' inside the workspace.
#
# Full tutorial: https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python bme280_reader
