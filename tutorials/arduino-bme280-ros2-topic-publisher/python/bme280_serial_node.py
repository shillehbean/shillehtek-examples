# ROS 2 Python node that opens a serial connection to the Arduino, parses CSV sensor lines, and publishes temperature, humidity, and pressure as a Float32MultiArray on the 'bme280_data' topic.
#
# Full tutorial: https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import rclpy
from rclpy.node import Node
import serial
from std_msgs.msg import Float32MultiArray

class BME280SerialNode(Node):
    def __init__(self):
        super().__init__('bme280_serial_reader')
        self.publisher_ = self.create_publisher(Float32MultiArray, 'bme280_data', 10)

        try:
            self.ser = serial.Serial('/dev/ttyACM1', 9600, timeout=1)
            self.get_logger().info("Connected to /dev/ttyACM1")
        except Exception as e:
            self.get_logger().error(f"Serial error: {e}")
            exit(1)

        self.timer = self.create_timer(2.0, self.read_serial)

    def read_serial(self):
        try:
            line = self.ser.readline().decode('utf-8').strip()
            if line:
                self.get_logger().info(f"RAW: {line}")
                parts = line.split(',')
                if len(parts) == 3:
                    temp = float(parts[0])
                    hum = float(parts[1])
                    pres = float(parts[2])
                    msg = Float32MultiArray(data=[temp, hum, pres])
                    self.publisher_.publish(msg)
        except Exception as e:
            self.get_logger().warn(f"Failed to read: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = BME280SerialNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
