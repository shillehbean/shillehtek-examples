// Arduino (Wire) example that performs a raw I2C read from the SHT45, verifies CRC-8 checksums, and converts the raw measurements to temperature and relative humidity.
//
// Buy this module: https://shillehtek.com/products/sht45-i2c-temperature-humidity-sensor-module-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sht45-i2c-temperature-humidity-sensor-module-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// GY-SHT45 temperature and humidity - raw I2C read (no library needed)
// Uno/Nano: SDA = A4, SCL = A5 through a 3.3 V level converter, VIN = 3.3V
// ESP32:    SDA = GPIO 21, SCL = GPIO 22, VIN = 3V3 (direct)
#include <Wire.h>

const uint8_t SHT45_ADDR = 0x44;
const uint8_t CMD_MEASURE_HIGH = 0xFD;   // high precision, heater off

float tempC = 0.0;
float humidity = 0.0;

// CRC-8 used by the SHT4x: polynomial 0x31, start value 0xFF
uint8_t crc8(const uint8_t *data, uint8_t len) {
  uint8_t crc = 0xFF;
  for (uint8_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (crc & 0x80) {
        crc = (uint8_t)((crc << 1) ^ 0x31);
      } else {
        crc = (uint8_t)(crc << 1);
      }
    }
  }
  return crc;
}

// Takes one measurement. Returns false if the sensor does not answer or a checksum fails.
bool readSHT45() {
  Wire.beginTransmission(SHT45_ADDR);
  Wire.write(CMD_MEASURE_HIGH);
  if (Wire.endTransmission() != 0) return false;
  delay(10);                               // a conversion takes up to 8.3 ms

  uint8_t buf[6];
  if (Wire.requestFrom((int)SHT45_ADDR, 6) != 6) return false;
  for (uint8_t i = 0; i < 6; i++) buf[i] = Wire.read();
  if (crc8(buf, 2) != buf[2] || crc8(buf + 3, 2) != buf[5]) return false;

  uint16_t rawT  = ((uint16_t)buf[0] << 8) | buf[1];
  uint16_t rawRH = ((uint16_t)buf[3] << 8) | buf[4];
  tempC    = -45.0 + 175.0 * rawT / 65535.0;
  humidity = -6.0 + 125.0 * rawRH / 65535.0;
  if (humidity < 0.0)   humidity = 0.0;
  if (humidity > 100.0) humidity = 100.0;
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  if (readSHT45()) {
    Serial.print("Temperature: ");
    Serial.print(tempC, 2);
    Serial.print(" C   Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %RH");
  } else {
    Serial.println("SHT45 read failed - check wiring and 3.3 V power");
  }
  delay(2000);
}
