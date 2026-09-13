# Add PICO_SDK_PATH to the user's zsh configuration and reload the shell environment.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-usb-serial-cpp-hello-world
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

echo 'export PICO_SDK_PATH=~/pico/pico-sdk' >> ~/.zshrc
source ~/.zshrc
