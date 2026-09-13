# Sources the workspace install overlay and echoes the '/bme280_data' ROS 2 topic to view published sensor messages.
#
# Full tutorial: https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

source ~/ros2_ws/install/setup.bash
ros2 topic echo /bme280_data
