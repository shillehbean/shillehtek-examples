# Downloads a file from the Pico to the host machine and saves it under a local filename via ampy.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-adafruit-ampy-run-code-cli
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

ampy --port /dev/ttyUSB0 get remote_file.py local_file.py
