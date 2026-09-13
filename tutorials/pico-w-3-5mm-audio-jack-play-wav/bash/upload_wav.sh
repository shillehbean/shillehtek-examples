# Install mpremote, locate the Pico serial device, set the PORT variable, and copy the prepared WAV file to the Pico filesystem.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-3-5mm-audio-jack-play-wav
# Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

python3 -m pip install --user mpremote

# Find the Pico serial port (usually /dev/cu.usbmodemXXXX)
ls /dev/cu.usb* /dev/tty.usb*

PORT=/dev/cu.usbmodemXXXX

# Copy the WAV to the Pico filesystem
mpremote connect $PORT fs cp ~/Downloads/kart.wav :kart.wav
