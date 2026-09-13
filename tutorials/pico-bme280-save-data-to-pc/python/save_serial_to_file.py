# Open a host serial port, read incoming data from the Pico, and save the received bytes to a local file until an EOF marker is received.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-bme280-save-data-to-pc
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import serial

# Configure the serial connection
port = "/dev/cu.usbmodem1101" 
baudrate = 115200
serial_connection = serial.Serial(port, baudrate)

# Open a file on your computer to write the received data
destination_file = open("/Users/mahmoodshilleh/Desktop/store_info.txt", "wb")

# Read and write data until the transfer is complete
while True:
    data = serial_connection.read(128)
    if data == b"EOF":
        break
    print(data)
    destination_file.write(data)

# Close the files and serial connection
destination_file.close()
serial_connection.close()
