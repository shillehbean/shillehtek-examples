# A MicroPython bit-banged 4-bit implementation for Pico-style boards that initializes the HD44780-compatible LCD and writes two lines of text directly via GPIO.
#
# Buy this module: https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lcd1602-16x2-character-display-module-manual
# More examples: https://github.com/shillehtek/examples
#

# LCD1602 16x2 LCD Display - Pico MicroPython Example
# Direct GPIO bit-banged 4-bit mode (no library needed).

from machine import Pin
import time

RS = Pin(15, Pin.OUT)
E  = Pin(14, Pin.OUT)
D4 = Pin(13, Pin.OUT)
D5 = Pin(12, Pin.OUT)
D6 = Pin(11, Pin.OUT)
D7 = Pin(10, Pin.OUT)

def pulse_e():
    E.value(1); time.sleep_us(1); E.value(0); time.sleep_us(50)

def write_nibble(value):
    D4.value((value >> 0) & 1)
    D5.value((value >> 1) & 1)
    D6.value((value >> 2) & 1)
    D7.value((value >> 3) & 1)
    pulse_e()

def write_byte(value, mode_data):
    RS.value(1 if mode_data else 0)
    write_nibble(value >> 4)
    write_nibble(value & 0x0F)

def cmd(c):  write_byte(c, False); time.sleep_ms(2)
def data(c): write_byte(c, True);  time.sleep_us(50)

def init_lcd():
    time.sleep_ms(50)
    write_nibble(0x03); time.sleep_ms(5)
    write_nibble(0x03); time.sleep_us(150)
    write_nibble(0x03); time.sleep_us(150)
    write_nibble(0x02)
    cmd(0x28)  # 4-bit, 2 line, 5x8
    cmd(0x0C)  # display on, no cursor
    cmd(0x06)  # entry mode
    cmd(0x01)  # clear

init_lcd()
for ch in "Hello, World!":
    data(ord(ch))
cmd(0xC0)  # row 2
for ch in "ShillehTek LCD":
    data(ord(ch))
