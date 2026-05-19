// MicroPython example for an ESP32 that initializes the SSD1306 over I2C and displays a few lines of static text.
//
// Buy this module: https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/0-96-i2c-white-oled-display-module-4-pin-ssd1306-manual
// More examples: https://github.com/shillehtek/examples
//

# 0.96" SSD1306 OLED - ESP32 MicroPython Example
# Upload ssd1306.py to the ESP32 first
# Wiring: SDA -> GPIO 21, SCL -> GPIO 22

from machine import Pin, I2C
import ssd1306

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=400_000)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

oled.fill(0)
oled.text("ShillehTek",   0, 0)
oled.text("SSD1306 OLED", 0, 16)
oled.text("ESP32 I2C",    0, 32)
oled.show()
