// Reads all four single-ended ADS1115 channels on an ESP32 (SDA=GPIO21, SCL=GPIO22) using the Adafruit ADS1X15 library and prints raw values and voltages over serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1115-4-channel-i2c-iic-analog-to-digital-adc-pga-16-bit-16-byte-converter
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ADS1115 on ESP32 via I2C (GPIO21 SDA, GPIO22 SCL)
// Requires: Adafruit ADS1X15 Library

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!ads.begin(0x48)) {
    Serial.println("ADS1115 not found.");
    while (1);
  }
  ads.setGain(GAIN_ONE); // +/- 4.096V
  Serial.println("ADS1115 ready.");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int16_t raw = ads.readADC_SingleEnded(i);
    float v   = ads.computeVolts(raw);
    Serial.printf("A%d: raw=%d  %.4f V\n", i, raw, v);
  }
  Serial.println();
  delay(500);
}
