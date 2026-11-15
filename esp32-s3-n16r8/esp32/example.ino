// Prints the ESP32-S3 chip model, flash and PSRAM sizes to serial and cycles the on-board RGB LED (GPIO 48) using the Arduino ESP32 core.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-n16r8-development-board-pre-soldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-n16r8-development-board-pre-soldered-headers-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32-S3 N16R8 board check - print flash and PSRAM size, cycle the RGB LED
// Arduino IDE: board "ESP32S3 Dev Module", Flash Size "16MB", PSRAM "OPI PSRAM"
// Needs the ESP32 board package 3.1 or newer (for rgbLedWrite). RGB LED = GPIO 48.
const int RGB_PIN = 48;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("Chip: ");
  Serial.println(ESP.getChipModel());
  Serial.print("Flash size (MB): ");
  Serial.println(ESP.getFlashChipSize() / 1048576.0, 1);
  Serial.print("PSRAM size (MB): ");
  Serial.println(ESP.getPsramSize() / 1048576.0, 1);
}

void loop() {
  rgbLedWrite(RGB_PIN, 32, 0, 0);    // red
  delay(500);
  rgbLedWrite(RGB_PIN, 0, 32, 0);    // green
  delay(500);
  rgbLedWrite(RGB_PIN, 0, 0, 32);    // blue
  delay(500);
  rgbLedWrite(RGB_PIN, 0, 0, 0);     // off
  delay(500);
}
