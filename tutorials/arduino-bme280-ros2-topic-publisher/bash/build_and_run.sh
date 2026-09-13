# Builds the ROS 2 workspace with colcon, sources the resulting install overlay, and runs the bme280_serial_node.
#
# Full tutorial: https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

cd ~/ros2_ws
colcon build
source install/setup.bash
ros2 run bme280_reader bme280_serial_node
