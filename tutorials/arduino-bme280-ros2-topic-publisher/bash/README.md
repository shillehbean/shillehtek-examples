# Bash examples

- [`install_ros_humble.sh`](./install_ros_humble.sh) — Installs ROS 2 Humble base packages and sources the ROS 2 environment on the Raspberry Pi.
- [`create_ros2_package.sh`](./create_ros2_package.sh) — Creates a ROS 2 workspace and a new Python package 'bme280_reader' inside the workspace.
- [`build_and_run.sh`](./build_and_run.sh) — Builds the ROS 2 workspace with colcon, sources the resulting install overlay, and runs the bme280_serial_node.
- [`echo_topic.sh`](./echo_topic.sh) — Sources the workspace install overlay and echoes the '/bme280_data' ROS 2 topic to view published sensor messages.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher)  
Parts used: [BME280 Pre-Soldered Temperature, Pressure & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [120pcs 20cm Dupont Jumper Wires for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire) · [Pre-Soldered I2C Logic Level Converter 3.3V-5V Bi-Directional for Arduino, Raspberry Pi, ESP32 & Pico](https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered)
