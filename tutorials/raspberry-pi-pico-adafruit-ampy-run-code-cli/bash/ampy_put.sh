# Uploads a local Python file to the Pico's filesystem over the specified serial port using ampy.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-adafruit-ampy-run-code-cli
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

ampy --port /dev/ttyUSB0 put your_file.py
