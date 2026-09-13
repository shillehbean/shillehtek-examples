# setup.py/setup.cfg entry_points snippet registering a console script entry point for the ROS 2 package so the node can be run via ros2 run.
#
# Full tutorial: https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

entry_points={
    'console_scripts': [
        'bme280_serial_node = bme280_reader.bme280_serial_node:main',
    ],
},
