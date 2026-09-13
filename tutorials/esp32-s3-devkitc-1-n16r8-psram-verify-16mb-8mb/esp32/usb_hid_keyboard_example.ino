// Initializes the ESP32-S3 USB HID keyboard and sends a short text string as a keyboard output.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-s3-devkitc-1-n16r8-psram-verify-16mb-8mb
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <USB.h>
#include <USBHIDKeyboard.h>

USBHIDKeyboard kb;

void setup() {
  USB.begin();
  kb.begin();
  delay(2000);
  kb.print("Hello from ESP32-S3!");
}

void loop() {
}
