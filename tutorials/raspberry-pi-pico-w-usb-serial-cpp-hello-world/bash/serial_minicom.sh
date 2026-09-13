# Open a serial terminal to the Pico using minicom at 115200 baud (replace device path as needed).
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-usb-serial-cpp-hello-world
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

minicom -b 115200 -o -D /dev/tty.usbmodemXXXX
