// Print the ESP32-P4 chip model and PSRAM size over serial, initialize I2C on SDA=GPIO7 SCL=GPIO8, and scan the I2C bus for devices (the ES8311 codec is expected at 0x18).
//
// Buy this module: https://shillehtek.com/products/esp32-p4-wifi-6-development-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-p4-wifi-6-development-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32-P4 Wi-Fi 6 kit check - print chip info and scan the on-board I2C bus
// Arduino IDE: ESP32 board package 3.2.0 or newer, board "ESP32P4 Dev Module"
// On-board I2C: SDA = GPIO 7, SCL = GPIO 8. The ES8311 audio codec should answer at 0x18.
#include <Wire.h>

const int PIN_SDA = 7;
const int PIN_SCL = 8;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("Chip: ");
  Serial.println(ESP.getChipModel());
  Serial.print("PSRAM size (MB): ");
  Serial.println(ESP.getPsramSize() / 1048576.0, 1);
  Wire.begin(PIN_SDA, PIN_SCL);
}

void loop() {
  int found = 0;
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device at 0x");
      Serial.println(address, HEX);
      found++;
    }
  }
  Serial.print("Devices found: ");
  Serial.println(found);
  delay(5000);
}
