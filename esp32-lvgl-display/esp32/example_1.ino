// TFT_eSPI configuration: defines the ILI9341 driver, screen dimensions, SPI and touch pins, SPI speeds, backlight pin state, and enabled fonts/features.
//
// Buy this module: https://shillehtek.com/products/Display
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-lvgl-2-8-inch-240x320-smart-display-with-resistive-touch-wifi-bluetooth-dev-board-manual
// More examples: https://github.com/shillehtek/examples
//

#define ILI9341_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST  -1   // tied to ESP32 reset
#define TFT_BL   21
#define TFT_BACKLIGHT_ON HIGH

#define TOUCH_CS 33

#define SPI_FREQUENCY       55000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_GFXFF
#define SMOOTH_FONT
