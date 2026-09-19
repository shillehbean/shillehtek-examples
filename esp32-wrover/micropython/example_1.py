# Shows esptool commands to flash a MicroPython SPIRAM build, then in the REPL prints CPU/flash info, reports free RAM and allocates a 2 MB bytearray in PSRAM to verify availability.
#
# Buy this module: https://shillehtek.com/products/esp32-wrover-4mb-psram-wifi-bluetooth-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-wrover-4mb-psram-wifi-bluetooth-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Flash MicroPython (SPIRAM build!) onto the WROVER over UART:
#   pip install esptool
#   esptool --port /dev/ttyUSB0 erase_flash
#   esptool --port /dev/ttyUSB0 --baud 460800 write_flash 0x1000 \
#       ESP32_GENERIC-SPIRAM-latest.bin
# (download the GENERIC-SPIRAM firmware from micropython.org)

# Then at the REPL:
import gc, esp, machine

print("CPU MHz:", machine.freq() // 1_000_000)
print("Flash size:", esp.flash_size())

gc.collect()
print("Free RAM:", gc.mem_free())   # ~4MB free = PSRAM active

# Allocate a 2MB bytearray - only possible with PSRAM
big = bytearray(2 * 1024 * 1024)
print("2MB bytearray OK, length:", len(big))
