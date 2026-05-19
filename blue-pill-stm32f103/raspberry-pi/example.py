# Instructions for flashing firmware.bin to the Blue Pill from a Raspberry Pi over UART using stm32flash: install stm32flash, set BOOT0=1, write to 0x08000000, then restore BOOT0 and reset.
#
# Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32-manual
# More examples: https://github.com/shillehtek/examples
#

# 1. Install stm32flash:
sudo apt update
sudo apt install stm32flash

# 2. Wire Pi UART to STM32 PA9/PA10 as shown in the wiring table.
# 3. Move BOOT0 jumper to 1 and press RESET on the Blue Pill.

# 4. Write firmware.bin starting at the Flash base address:
sudo stm32flash -w firmware.bin -v -g 0x8000000 /dev/serial0

# 5. Move BOOT0 jumper back to 0 and press RESET to run your firmware.
