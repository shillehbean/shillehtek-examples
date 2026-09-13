# Assemble captured JPEG frame files into a 30 fps H.264-encoded MP4 timelapse using ffmpeg.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-4b-camera-module-build-timelapse
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

ffmpeg -framerate 30 -pattern_type glob -i 'frame_*.jpg' -c:v libx264 -pix_fmt yuv420p timelapse.mp4
