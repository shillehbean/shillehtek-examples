// Uses the Adafruit TSL2591 library on Arduino/ESP32 to read full-spectrum and IR channels, calculate lux, and print readings over Serial.
//
// Buy this module: https://shillehtek.com/products/tsl2591-light-sensor-presoldered-purple-breakout-single
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tsl2591-light-sensor-presoldered-purple-breakout-single-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TSL2591 light sensor - lux, visible and infrared readings
// Library Manager: install "Adafruit TSL2591 Library" (it pulls in Adafruit Unified Sensor)
// Uno/Nano: SDA = A4, SCL = A5, VIN = 5V     ESP32: SDA = GPIO 21, SCL = GPIO 22, VIN = 3V3
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2591.h>

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);   // the number is only a sensor ID

void setup() {
  Serial.begin(115200);
  if (!tsl.begin()) {
    Serial.println("TSL2591 not found - check wiring (I2C address 0x29)");
    while (true) { delay(1000); }
  }
  tsl.setGain(TSL2591_GAIN_MED);                  // 25x suits indoor light
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);   // longer time = more sensitive
}

void loop() {
  uint32_t both = tsl.getFullLuminosity();   // upper 16 bits = infrared, lower 16 = full spectrum
  uint16_t ir   = both >> 16;
  uint16_t full = both & 0xFFFF;
  float lux = tsl.calculateLux(full, ir);

  Serial.print("Full: ");
  Serial.print(full);
  Serial.print("   IR: ");
  Serial.print(ir);
  Serial.print("   Lux: ");
  if (lux < 0) {
    Serial.println("overflow - lower the gain");
  } else {
    Serial.println(lux, 2);
  }
  delay(1000);
}
