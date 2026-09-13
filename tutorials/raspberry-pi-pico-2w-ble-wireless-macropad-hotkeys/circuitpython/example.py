# CircuitPython script that advertises a BLE HID keyboard and sends predefined hotkey combinations when six GPIO-connected switches are pressed.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-2w-ble-wireless-macropad-hotkeys
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
#             https://shillehtek.com/products/raspberry-pi-pico-2-usb-c-presoldered-headers
#             https://shillehtek.com/products/351015-500mah-3-7v-lithium-rechargeable-battery-3-5-x-10-x-15mm
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import board, digitalio
from adafruit_ble import BLERadio
from adafruit_ble.advertising import Advertisement
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.standard.hid import HIDService
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

hid = HIDService()
adv = ProvideServicesAdvertisement(hid)
adv.appearance = 961  # generic keyboard
ble = BLERadio()
if not ble.connected:
    ble.start_advertising(adv)
kbd = Keyboard(hid.devices)

# wire each GPIO to a switch
PINS = [board.GP2, board.GP3, board.GP4, board.GP5, board.GP6, board.GP7]
KEYS = [
    [Keycode.CONTROL, Keycode.C],       # copy
    [Keycode.CONTROL, Keycode.V],       # paste
    [Keycode.CONTROL, Keycode.Z],       # undo
    [Keycode.WINDOWS, Keycode.TAB],     # task switcher
    [Keycode.F5],                       # refresh
    [Keycode.MUTE],                     # mute audio
]
buttons = []
for p in PINS:
    b = digitalio.DigitalInOut(p)
    b.direction = digitalio.Direction.INPUT
    b.pull = digitalio.Pull.UP
    buttons.append(b)

last = [True] * 6
while True:
    for i, b in enumerate(buttons):
        if not b.value and last[i]:  # falling edge: pressed
            kbd.press(*KEYS[i])
            kbd.release_all()
            time.sleep(0.03)
        last[i] = b.value
    time.sleep(0.005)
