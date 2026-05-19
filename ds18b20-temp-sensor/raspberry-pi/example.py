# Uses the Raspberry Pi 1-Wire kernel driver to read a DS18B20 device file and print the temperature in Celsius and Fahrenheit in a loop.
#
# Buy this module: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# DS18B20 on Raspberry Pi via 1-Wire kernel driver
# Enable 1-Wire first: sudo raspi-config -> Interface Options -> 1-Wire

import glob, time

base = "/sys/bus/w1/devices/"
device = glob.glob(base + "28-*")[0] + "/w1_slave"

def read_temp():
    with open(device, "r") as f:
        lines = f.readlines()
    while not lines[0].strip().endswith("YES"):
        time.sleep(0.2)
        with open(device, "r") as f:
            lines = f.readlines()
    pos = lines[1].find("t=")
    if pos != -1:
        return float(lines[1][pos+2:]) / 1000.0
    return None

while True:
    c = read_temp()
    print("Temp: {:.2f} C  /  {:.2f} F".format(c, c * 9/5 + 32))
    time.sleep(1)
