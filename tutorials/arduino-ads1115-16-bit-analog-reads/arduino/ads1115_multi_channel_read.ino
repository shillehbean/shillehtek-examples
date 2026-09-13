// Reads all four ADS1115 single-ended channels over I2C and prints raw ADC values and converted voltages to the serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ads1115-16-bit-analog-reads
// Parts used: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(9600);
  if (!ads.begin()) { Serial.println("ADS1115 not found"); while (1); }
  ads.setGain(GAIN_TWOTHIRDS);   // .144 V full-scale
}

void loop() {
  for (int ch = 0; ch < 4; ch++) {
    int16_t raw = ads.readADC_SingleEnded(ch);
    float volts = ads.computeVolts(raw);
    Serial.print("CH"); Serial.print(ch);
    Serial.print(" raw="); Serial.print(raw);
    Serial.print(" V="); Serial.print(volts, 4);
    Serial.print("   ");
  }
  Serial.println();
  delay(500);
}
