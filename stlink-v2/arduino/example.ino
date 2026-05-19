// PlatformIO environment configuration to build and upload Arduino-framework firmware to Blue Pill or Black Pill STM32 boards using the ST-LINK V2 as the upload and debug tool.
//
// Buy this module: https://shillehtek.com/products/st-link-v2-stm8-stm32-programmer-downloader
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/st-link-v2-stm8-stm32-programmer-downloader-manual
// More examples: https://github.com/shillehtek/examples
//

; PlatformIO config for a Blue Pill flashed via ST-LINK V2
; Put this in your project root and run: pio run --target upload

[env:bluepill_f103c8]
platform = ststm32
board = bluepill_f103c8
framework = arduino

; Upload using the ST-LINK V2 (default is serial)
upload_protocol = stlink
debug_tool = stlink

; Optional: speed up the SWD clock
upload_flags = -c set CPUTAPID 0x1ba01477

[env:blackpill_f411ce]
platform = ststm32
board = blackpill_f411ce
framework = arduino
upload_protocol = stlink
debug_tool = stlink
