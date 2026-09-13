# Install ffmpeg (macOS) and convert an input WAV to 8-bit mono PCM at 8000 Hz suitable for the Pico playback code.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-3-5mm-audio-jack-play-wav
# Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

brew install ffmpeg

cd ~/Downloads

# Example input name from this build:
ffmpeg -y -i smb_stage_clear.wav -ac 1 -ar 8000 -acodec pcm_u8 kart.wav
