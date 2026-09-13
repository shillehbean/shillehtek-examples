# CircuitPython example that watches a GPIO button and sends Ctrl+C over USB HID while the button is held.
#
# Full tutorial: https://shillehtek.com/blogs/news/seeeduino-xiao-samd21-usb-hid-macro-numpad
# Parts used: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
#             https://shillehtek.com/products/4x4-membrane-matrix-keypad-16-key-switch-module-for-arduino-diy
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import board, digitalio, usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

kbd = Keyboard(usb_hid.devices)
btn = digitalio.DigitalInOut(board.D0)
btn.switch_to_input(pull=digitalio.Pull.UP)

while True:
    if not btn.value:
        kbd.send(Keycode.CONTROL, Keycode.C)
        while not btn.value:
            pass
