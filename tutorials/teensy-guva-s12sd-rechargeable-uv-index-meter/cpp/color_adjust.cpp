// Utility function that increases the red component of a 16-bit RGB565 color based on an index value while clamping to avoid overflow of the 5 red bits.
//
// Full tutorial: https://shillehtek.com/blogs/news/teensy-guva-s12sd-rechargeable-uv-index-meter
// Parts used: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

uint16_t adjust_redness(uint16_t color, int index) {
  // color format: RRRRR-GGGGGG-BBBBB
  int r = color >> 11;
  int new_r = r + (r * index / 5);
  if (new_r > 0b11111) {
    new_r = 0b11111; // don't overflow the 5 red bits
  }
  uint16_t new_color = (color & 0b0000011111111111) | (new_r << 11);
  return new_color;
}
