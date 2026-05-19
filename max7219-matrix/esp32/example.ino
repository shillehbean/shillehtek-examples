// Runs on an ESP32 using the micropython-max7219 driver to scroll a message across four cascaded 8x8 matrices via SPI with the specified GPIO pins (DIN->GPIO23, CS->GPIO5, CLK->GPIO18).
//
// Buy this module: https://shillehtek.com/products/max7219-4-in-1-dot-matrix-display-module-red
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max7219-4-in-1-dot-matrix-display-module-red-manual
// More examples: https://github.com/shillehtek/examples
//

# MAX7219 4-in-1 Dot Matrix - ESP32 MicroPython Scrolling Text
# Upload max7219.py to the ESP32 first
# Wiring: DIN -> GPIO 23, CS -> GPIO 5, CLK -> GPIO 18

from machine import Pin, SPI
import max7219
import time

spi = SPI(2, baudrate=10_000_000, polarity=0, phase=0,
          sck=Pin(18), mosi=Pin(23))
cs  = Pin(5, Pin.OUT)

display = max7219.Matrix8x8(spi, cs, 4)
display.brightness(5)
display.fill(0)

message = " ShillehTek ESP32 MAX7219 "
while True:
    for pos in range(len(message) * 8):
        display.fill(0)
        display.text(message, -pos, 0, 1)
        display.show()
        time.sleep(0.04)
