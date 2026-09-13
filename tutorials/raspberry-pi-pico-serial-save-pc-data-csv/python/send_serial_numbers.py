# Sends the integers 1–1000 as comma-separated values over a serial port at 115200 baud to a connected device.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-serial-save-pc-data-csv
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import serial
import time

# Configure the serial connection
port = "/dev/cu.usbmodem11201"  # Adjust the port to match your setup
baudrate = 115200
serial_connection = serial.Serial(port, baudrate)

# Read and write data until the transfer is complete
for i in range(1, 1001):
    print(i)
    serial_connection.write((str(i) + ',').encode())
    time.sleep(0.01)

time.sleep(10)
serial_connection.close()
