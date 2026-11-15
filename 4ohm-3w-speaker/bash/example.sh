# Interactive Raspberry Pi setup instructions: edit /boot/firmware/config.txt on Bookworm or later (/boot/config.txt on older releases), enable the MAX98357 I2S overlay, reboot, and check playback with aplay and speaker-test.
#
# Buy this module: https://shillehtek.com/products/mini-speaker-4ohm-3w-square-150mm-dupont-lead
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-speaker-4ohm-3w-square-150mm-dupont-lead-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Raspberry Pi OS Bookworm and later: /boot/firmware/config.txt
# Older releases: /boot/config.txt
sudo nano /boot/firmware/config.txt
#   1) Put a # in front of this line:   dtparam=audio=on
#   2) Add this line:                   dtoverlay=max98357a
sudo reboot

# After the reboot:
aplay -l                        # the MAX98357 card should be listed
speaker-test -c2 -t wav -l 1    # plays a spoken channel test once
