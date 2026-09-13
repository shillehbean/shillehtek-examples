# Remotely executes a Python script on the Pico without permanently copying it to the device using ampy run.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-adafruit-ampy-run-code-cli
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

ampy --port /dev/ttyUSB0 run your_script.py
