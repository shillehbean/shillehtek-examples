# stm8flash commands to read device info, unlock read-protection options, and flash firmware to STM8 microcontrollers over SWIM using the ST-LINK V2.
#
# Buy this module: https://shillehtek.com/products/st-link-v2-stm8-stm32-programmer-downloader
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/st-link-v2-stm8-stm32-programmer-downloader-manual
# More examples: https://github.com/shillehtek/examples
#

# Flash an STM8 chip over SWIM using stm8flash + ST-LINK V2
# Install from source: https://github.com/vdudouyt/stm8flash

# Read chip info (use your actual part number)
stm8flash -c stlinkv2 -p stm8s103f3 -s opt -r options.bin

# Unlock the chip if it's in read-out protection
stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w default_opt.bin

# Flash the main application to flash memory
stm8flash -c stlinkv2 -p stm8s103f3 -s flash -w firmware.ihx

# Common -p values: stm8s103f3, stm8s003f3, stm8s105k4,
# stm8l151f3, stm8af5288, stm8l051f3
