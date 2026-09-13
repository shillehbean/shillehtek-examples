// Main Arduino sketch that initializes the screen, reads battery percentage and UV index periodically, and updates the display only when values change.
//
// Full tutorial: https://shillehtek.com/blogs/news/teensy-guva-s12sd-rechargeable-uv-index-meter
// Parts used: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "TFT_display.h"
#include "battery.h"
#include "UV_sensor.h"
float last_percent = 100;
float last_index = 100;
float percent_now;
float index_now;

void setup(void) {
  Serial.begin(9600);
  init_screen();
}

void loop() {
  percent_now = bat_percentage();
  index_now = UV_index();

  // only update the screen if a reading changed
  if (percent_now != last_percent) {
    display_battery(percent_now);
    last_percent = percent_now;
  }
  if (index_now != last_index) {
    display_texts(index_now);
    display_pic(index_now);
    last_index = index_now;
  }
  delay(1000);
}
