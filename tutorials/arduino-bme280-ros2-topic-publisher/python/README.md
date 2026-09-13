# Python examples

- [`bme280_serial_node.py`](./bme280_serial_node.py) — ROS 2 Python node that opens a serial connection to the Arduino, parses CSV sensor lines, and publishes temperature, humidity, and pressure as a Float32MultiArray on the 'bme280_data' topic.
- [`setup.py`](./setup.py) — setup.py/setup.cfg entry_points snippet registering a console script entry point for the ROS 2 package so the node can be run via ros2 run.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher)  
Parts used: [BME280 Pre-Soldered Temperature, Pressure & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [120pcs 20cm Dupont Jumper Wires for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire) · [Pre-Soldered I2C Logic Level Converter 3.3V-5V Bi-Directional for Arduino, Raspberry Pi, ESP32 & Pico](https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered)
