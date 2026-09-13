// Prints CPU frequency, flash size, PSRAM size, and free PSRAM to the Serial console for verification.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-s3-devkitc-1-n16r8-psram-verify-16mb-8mb
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.printf("CPU @ %d MHz\n", getCpuFrequencyMhz());
  Serial.printf("Flash size: %d MB\n", ESP.getFlashChipSize() / (1024*1024));
  Serial.printf("PSRAM size: %d KB\n", ESP.getPsramSize() / 1024);
  Serial.printf("Free PSRAM: %d KB\n", ESP.getFreePsram() / 1024);
}

void loop() {
  delay(1000);
}
