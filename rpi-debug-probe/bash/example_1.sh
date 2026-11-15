# Installs OpenOCD and gdb-multiarch, then programs a previously built blink.elf to a Pico over CMSIS-DAP/SWD; supply that ELF file before running the programming command.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-debug-probe-swd-uart-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-debug-probe-swd-uart-kit-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Install the tools (Raspberry Pi OS, Debian, Ubuntu)
sudo apt install openocd gdb-multiarch

# Flash an ELF file to a Pico over SWD, then reset and run it
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program blink.elf verify reset exit"
