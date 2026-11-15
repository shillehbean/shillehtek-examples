// Read the MAX17048 VCELL and SOC registers over I2C on an Arduino/ESP board and print battery voltage and percentage to the serial console.
//
// Buy this module: https://shillehtek.com/products/max17048-i2c-single-cell-fuel-gauge-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max17048-i2c-single-cell-fuel-gauge-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MAX17048 battery fuel gauge - read cell voltage and state of charge over I2C
// Arduino Uno/Nano: VIN = 5V, SDA = A4, SCL = A5.  ESP32: VIN = 3V3, SDA = GPIO 21, SCL = GPIO 22.
// GND = GND. A battery must be plugged into the board, or the chip will not answer.
#include <Wire.h>

const uint8_t MAX17048_ADDR = 0x36;
const uint8_t REG_VCELL = 0x02;    // cell voltage, 78.125 uV per count
const uint8_t REG_SOC   = 0x04;    // state of charge, 1/256 % per count

bool readRegister(uint8_t reg, uint16_t &value) {
  Wire.beginTransmission(MAX17048_ADDR);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom((int)MAX17048_ADDR, 2) != 2) return false;
  uint8_t high = Wire.read();
  uint8_t low = Wire.read();
  value = ((uint16_t)high << 8) | low;
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  uint16_t rawVolts, rawPercent;
  if (readRegister(REG_VCELL, rawVolts) && readRegister(REG_SOC, rawPercent)) {
    Serial.print("Battery: ");
    Serial.print(rawVolts * 78.125 / 1000000.0, 3);
    Serial.print(" V  ");
    Serial.print(rawPercent / 256.0, 1);
    Serial.println(" %");
  } else {
    Serial.println("MAX17048 not found - is a battery connected?");
  }
  delay(2000);
}
