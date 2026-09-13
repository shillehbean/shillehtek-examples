// Initializes an SSD1306 OLED object and provides a helper function to estimate gas ppm from a raw analog reading (placeholder calibration values).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mq-2-gas-leak-alarm
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

float estimatePPM(int raw) {
  float Rs = (1023.0 / raw - 1.0) * 5.0;   // sensor resistance
  // For LPG curve (datasheet): ppm = 574 * (Rs/Ro)^-2.07
  // Ro ~ baseline_rs * 10 (assume air baseline)
  float ratio = Rs / 30.0;     // placeholder for Ro
  return 574.0 * pow(ratio, -2.07);
}
