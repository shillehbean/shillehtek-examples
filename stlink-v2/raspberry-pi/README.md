# Raspberry Pi examples

- [`example_1.py`](./example_1.py) — Host CLI steps using STM32_Programmer_CLI to connect to an STM32 via ST-LINK V2, read chip ID, erase flash, write/verify firmware, reset and back up flash.
- [`example_2.py`](./example_2.py) — OpenOCD commands to program STM32 targets with the ST-LINK V2 and to start an interactive debug session that connects GDB to the target via OpenOCD.
- [`example_3.py`](./example_3.py) — stm8flash commands to read device info, unlock read-protection options, and flash firmware to STM8 microcontrollers over SWIM using the ST-LINK V2.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/st-link-v2-stm8-stm32-programmer-downloader-manual)  
Buy the module: https://shillehtek.com/products/st-link-v2-stm8-stm32-programmer-downloader
