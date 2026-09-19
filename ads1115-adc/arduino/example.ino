// Reads all four single-ended ADS1115 channels on an Arduino using the Adafruit ADS1X15 library and prints raw counts and computed voltages over serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1115-4-channel-i2c-iic-analog-to-digital-adc-pga-16-bit-16-byte-converter
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ADS1115 - Read all 4 single-ended channels
// Requires: Adafruit ADS1X15 Library

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!ads.begin(0x48)) {
    Serial.println("Failed to initialize ADS1115.");
    while (1);
  }

  // PGA = +/- 4.096V => 1 bit = 0.125 mV
  ads.setGain(GAIN_ONE);
  Serial.println("ADS1115 ready.");
}

void loop() {
  int16_t raw[4];
  float volts[4];
  for (int i = 0; i < 4; i++) {
    raw[i] = ads.readADC_SingleEnded(i);
    volts[i] = ads.computeVolts(raw[i]);
    Serial.print("A");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(raw[i]);
    Serial.print("  ");
    Serial.print(volts[i], 4);
    Serial.print(" V   ");
  }
  Serial.println();
  delay(500);
}
