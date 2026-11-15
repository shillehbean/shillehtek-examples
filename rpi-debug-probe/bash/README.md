# Bash examples

- [`example_1.sh`](./example_1.sh) — Installs OpenOCD and gdb-multiarch, then programs a previously built blink.elf to a Pico over CMSIS-DAP/SWD; supply that ELF file before running the programming command.
- [`example_2.sh`](./example_2.sh) — Installs minicom and opens the probe UART at 115200 baud; replace /dev/ttyACM0 if the system assigns a different device.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-debug-probe-swd-uart-kit-manual)  
Buy the module: https://shillehtek.com/products/raspberry-pi-debug-probe-swd-uart-kit
