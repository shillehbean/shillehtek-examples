# OpenOCD commands to program STM32 targets with the ST-LINK V2 and to start an interactive debug session that connects GDB to the target via OpenOCD.
#
# Buy this module: https://shillehtek.com/products/st-link-v2-stm8-stm32-programmer-downloader
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/st-link-v2-stm8-stm32-programmer-downloader-manual
# More examples: https://github.com/shillehtek/examples
#

# Flash firmware with OpenOCD + ST-LINK V2
# Install: sudo apt install openocd  (Debian/Ubuntu)
#          brew install open-ocd     (macOS)

# Blue Pill (STM32F1x)
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
  -c "program firmware.hex verify reset exit"

# Black Pill (STM32F4x)
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
  -c "program firmware.hex verify reset exit"

# Interactive debug session (connect GDB on port 3333)
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg

# In another terminal:
arm-none-eabi-gdb firmware.elf
(gdb) target remote localhost:3333
(gdb) monitor reset halt
(gdb) load
(gdb) continue
