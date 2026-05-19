# Host CLI steps using STM32_Programmer_CLI to connect to an STM32 via ST-LINK V2, read chip ID, erase flash, write/verify firmware, reset and back up flash.
#
# Buy this module: https://shillehtek.com/products/st-link-v2-stm8-stm32-programmer-downloader
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/st-link-v2-stm8-stm32-programmer-downloader-manual
# More examples: https://github.com/shillehtek/examples
#

# Flash a .hex or .bin file to an STM32 using ST-LINK V2
# Install: https://www.st.com/en/development-tools/stm32cubeprog.html
# The CLI tool is called STM32_Programmer_CLI on Linux/macOS
# and STM32_Programmer_CLI.exe on Windows

# 1) Connect and read the chip ID (sanity check)
STM32_Programmer_CLI -c port=SWD freq=4000

# 2) Erase the entire flash
STM32_Programmer_CLI -c port=SWD -e all

# 3) Flash a hex file and verify, then reset and run
STM32_Programmer_CLI -c port=SWD \
  -w firmware.hex \
  -v \
  -rst

# 4) Read flash back to a file (for backup)
STM32_Programmer_CLI -c port=SWD \
  -r32 0x08000000 0x10000 backup.hex
