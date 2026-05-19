# MicroPython snippet that initializes the camera, connects the board to Wi‑Fi, and repeatedly captures JPEG frames printing the captured buffer sizes.
#
# Buy this module: https://shillehtek.com/products/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam-manual
# More examples: https://github.com/shillehtek/examples
#

# MicroPython on ESP32-CAM
# Flash with the camera-enabled firmware from
# https://github.com/lemariva/micropython-camera-driver
# Then run this snippet:

import camera, network, time
camera.init(0, format=camera.JPEG, framesize=camera.FRAME_HD)

wlan = network.WLAN(network.STA_IF); wlan.active(True)
wlan.connect("SSID", "PASS")
while not wlan.isconnected(): time.sleep(0.5)
print("IP:", wlan.ifconfig()[0])

while True:
    buf = camera.capture()
    print(f"Captured {len(buf)} bytes")
    time.sleep(2)
