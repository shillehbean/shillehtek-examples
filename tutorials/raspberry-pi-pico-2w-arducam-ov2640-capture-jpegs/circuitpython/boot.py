# Boot-time configuration to enable the USB serial REPL and remount the internal flash filesystem read-write so the script can create and write files.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-2w-arducam-ov2640-capture-jpegs
# Parts used: https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import storage, usb_cdc
# Keep serial REPL working
usb_cdc.enable(console=True, data=True)
# Make internal flash writable by your code (host will see it read-only)
storage.remount("/", readonly=False)
