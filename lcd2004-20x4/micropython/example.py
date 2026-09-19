# MicroPython driver for Pico that implements low-level 4-bit signaling (RS/E/D4–D7), initialization, cursor positioning, and text writing for a 20x4 HD44780-compatible LCD.
#
# Buy this module: https://shillehtek.com/products/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# LCD2004 20x4 Character LCD - Pico MicroPython Example (4-bit mode)
# RS->GP16, E->GP17, D4-D7->GP18/19/20/21, RW->GND, VDD->VBUS(5V)

from machine import Pin
import time

RS = Pin(16, Pin.OUT)
E  = Pin(17, Pin.OUT)
DATA = [Pin(p, Pin.OUT) for p in (18, 19, 20, 21)]   # D4..D7
ROW_ADDR = (0x00, 0x40, 0x14, 0x54)                  # 20x4 row offsets

def pulse():
    E.value(1); time.sleep_us(2)
    E.value(0); time.sleep_us(50)

def write4(nib):
    for i in range(4):
        DATA[i].value((nib >> i) & 1)
    pulse()

def write_byte(b, rs):
    RS.value(rs)
    write4(b >> 4)
    write4(b & 0x0F)

def cmd(b):  write_byte(b, 0); time.sleep_ms(2)
def char(c): write_byte(ord(c), 1)

def lcd_init():
    time.sleep_ms(40)
    RS.value(0)
    for _ in range(3):
        write4(0x03); time.sleep_ms(5)
    write4(0x02)              # 4-bit mode
    cmd(0x28)                 # 2-line logical, 5x8 font
    cmd(0x0C)                 # display on, cursor off
    cmd(0x06)                 # entry mode: increment
    cmd(0x01)                 # clear
    time.sleep_ms(2)

def goto(row, col):
    cmd(0x80 | (ROW_ADDR[row] + col))

def text(row, s):
    goto(row, 0)
    for c in s[:20]:
        char(c)

lcd_init()
text(0, "ShillehTek LCD2004")
text(1, "Pico MicroPython")
text(2, "4-bit, RW to GND")

count = 0
while True:
    text(3, "Uptime: {} s".format(count))
    count += 1
    time.sleep(1)
