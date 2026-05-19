// Shows how to use the sh1106 MicroPython driver on an ESP32 over I2C to display static text on the OLED.
//
// Buy this module: https://shillehtek.com/products/1-3-i2c-white-oled-display-module-4-pin-sh1106
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-3-i2c-white-oled-display-module-4-pin-sh1106-manual
// More examples: https://github.com/shillehtek/examples
//

# 1.3" SH1106 OLED - ESP32 MicroPython Example
# Upload sh1106.py to the ESP32 first
# Wiring: SDA -> GPIO 21, SCL -> GPIO 22

from machine import Pin, I2C
import sh1106

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=400_000)
oled = sh1106.SH1106_I2C(128, 64, i2c, None, 0x3C)

oled.fill(0)
oled.text("ShillehTek",  0, 0)
oled.text("SH1106 OLED", 0, 16)
oled.text("ESP32 I2C",   0, 32)
oled.show()
