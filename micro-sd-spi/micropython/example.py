# On a MicroPython board (e.g., RP2040 Pico) mounts an SD card over SPI, writes 'Hello from Pico!' to /sd/test.txt, and reads back the file contents.
#
# Buy this module: https://shillehtek.com/products/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

import machine, sdcard, uos

spi = machine.SPI(0, baudrate=1000000,
                  sck=machine.Pin(2), mosi=machine.Pin(3), miso=machine.Pin(4))
cs = machine.Pin(5, machine.Pin.OUT)
sd = sdcard.SDCard(spi, cs)
uos.mount(sd, '/sd')

with open('/sd/test.txt', 'w') as f:
    f.write('Hello from Pico!')

with open('/sd/test.txt') as f:
    print(f.read())
