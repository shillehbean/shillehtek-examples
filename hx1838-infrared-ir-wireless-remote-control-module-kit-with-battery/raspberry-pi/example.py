# Uses pigpio on a Raspberry Pi to capture raw GPIO edge timings from the IR receiver and print level changes with microsecond timing.
#
# Buy this module: https://shillehtek.com/products/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: sudo apt install pigpio python3-pigpio
# Start daemon: sudo systemctl enable --now pigpiod

# Quick raw-pulse capture using pigpio
import pigpio, time, sys

GPIO_PIN = 17

pi = pigpio.pi()
pi.set_mode(GPIO_PIN, pigpio.INPUT)

last_tick = 0
def cbf(gpio, level, tick):
    global last_tick
    diff = pigpio.tickDiff(last_tick, tick)
    last_tick = tick
    print(f"{level} after {diff} us")

cb = pi.callback(GPIO_PIN, pigpio.EITHER_EDGE, cbf)
print("Press buttons. Ctrl-C to stop.")
try:
    while True: time.sleep(1)
except KeyboardInterrupt:
    cb.cancel()
    pi.stop()
