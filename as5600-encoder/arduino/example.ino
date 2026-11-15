// Read AS5600 status and the 12-bit raw angle over I2C using the Arduino/Wire library and print results to Serial.
//
// Buy this module: https://shillehtek.com/products/as5600-magnetic-encoder-pre-soldered-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/as5600-magnetic-encoder-pre-soldered-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// AS5600 magnetic encoder - read the angle over I2C (no library needed)
// Uno/Nano: SDA = A4, SCL = A5 through a 3.3 V level converter, VCC = 3.3V
// ESP32:    SDA = GPIO 21, SCL = GPIO 22, VCC = 3V3 (direct)
#include <Wire.h>

const uint8_t AS5600_ADDR   = 0x36;
const uint8_t REG_STATUS    = 0x0B;   // bit 5 = magnet detected, bit 4 = too weak, bit 3 = too strong
const uint8_t REG_RAW_ANGLE = 0x0C;   // 12-bit raw angle, high byte first

// Reads 1 or 2 bytes starting at reg. Returns -1 if the sensor does not answer.
int readRegister(uint8_t reg, uint8_t count) {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return -1;
  Wire.requestFrom((int)AS5600_ADDR, (int)count);
  if (Wire.available() < count) return -1;
  int value = 0;
  for (uint8_t i = 0; i < count; i++) {
    value = (value << 8) | Wire.read();
  }
  return value;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(100);

  int status = readRegister(REG_STATUS, 1);
  if (status < 0) {
    Serial.println("AS5600 not found - check wiring and 3.3 V power");
    while (true) { delay(1000); }
  }
  if (!(status & 0x20)) Serial.println("No magnet detected - center it over the chip");
  if (status & 0x10)    Serial.println("Magnet too weak - move it closer");
  if (status & 0x08)    Serial.println("Magnet too strong - move it away");
}

void loop() {
  int raw = readRegister(REG_RAW_ANGLE, 2);
  if (raw >= 0) {
    raw &= 0x0FFF;                          // keep the 12 valid bits
    float degrees = raw * 360.0 / 4096.0;   // 4096 steps per turn
    Serial.print("Raw: ");
    Serial.print(raw);
    Serial.print("   Angle: ");
    Serial.print(degrees, 1);
    Serial.println(" deg");
  }
  delay(100);
}
