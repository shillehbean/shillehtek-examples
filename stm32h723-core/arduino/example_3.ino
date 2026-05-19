// PlatformIO environment configuration for building Arduino-framework firmware for the STM32H723ZGT6 (genericSTM32H723ZG) and uploading/debugging with ST-Link, with a serial monitor at 115200 baud.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-stm32h723zgt6-core-development-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-stm32h723zgt6-core-development-board-manual
// More examples: https://github.com/shillehtek/examples
//

; PlatformIO config for STM32H723ZGT6
[env:stm32h723zg]
platform = ststm32
board = genericSTM32H723ZG
framework = arduino
upload_protocol = stlink
debug_tool = stlink
monitor_speed = 115200
