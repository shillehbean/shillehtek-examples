# Bash examples

- [`example_1.sh`](./example_1.sh) — Linux/flashrom workflow: install flashrom, probe the CH341A, read the flash twice and compare hashes, write a new firmware image (flashrom erases and verifies), and explicitly verify a file when needed.
- [`example_2.sh`](./example_2.sh) — I2C EEPROM tools: GUI route using imsprog on Debian/Ubuntu/Raspberry Pi OS to read/write 24Cxx parts, and CLI route using the ch341eeprom utility to read and write 24C64 chips.
- [`example_3.sh`](./example_3.sh) — Raspberry Pi flashrom example: install flashrom on Raspberry Pi OS, read a connected SPI flash with the CH341A and compute a checksum, plus an optional udev rule to allow non-root access to the device.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/ch341a-usb-eeprom-bios-programmer-manual)  
Buy the module: https://shillehtek.com/products/ch341a-usb-eeprom-bios-programmer
