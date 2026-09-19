// Reads the AMG8833 thermal sensor over I2C and prints an 8x8 temperature matrix to the serial port at 500 ms intervals.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-amg8833-thermal-camera-pc-heatmap
// Parts used: https://shillehtek.com/products/amg8833-ir-thermal-camera-sensor-arduino-esp32
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Melopero_AMG8833.h>

Melopero_AMG8833 sensor;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.initI2C();
  sensor.resetFlagsAndSettings();
  sensor.setFPSMode(FPS_MODE::FPS_10);
}

void loop() {
  sensor.updatePixelMatrix();
  for (byte r = 0; r < 8; r++) {
    for (byte c = 0; c < 8; c++) {
      Serial.print(sensor.pixelMatrix[r][c], 1);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
  delay(500);
}
