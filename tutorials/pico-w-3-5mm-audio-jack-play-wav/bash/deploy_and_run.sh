# Copy the play_wav.py script to the Pico and run it over the serial connection using mpremote.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-3-5mm-audio-jack-play-wav
# Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

PORT=/dev/cu.usbmodemXXXX

mpremote connect $PORT fs cp ~/Downloads/play_wav.py :play_wav.py
mpremote connect $PORT run play_wav.py
