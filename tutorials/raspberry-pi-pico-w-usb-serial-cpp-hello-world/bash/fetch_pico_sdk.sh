# Create a pico workspace, clone the Raspberry Pi pico-sdk repository, and initialize its submodules.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-usb-serial-cpp-hello-world
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

mkdir -p ~/pico
cd ~/pico
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
