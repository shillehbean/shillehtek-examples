# Raspberry Pi examples

- [`example.py`](./example.py) — Instructions for flashing firmware.bin to the Blue Pill from a Raspberry Pi over UART using stm32flash: install stm32flash, set BOOT0=1, write to 0x08000000, then restore BOOT0 and reset.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32-manual)  
Buy the module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
