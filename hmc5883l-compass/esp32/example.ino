// ESP32 (Arduino core) example that initializes I2C on GPIO21/22, uses the Adafruit HMC5883 library to read magnetic axes, and prints X/Y values and heading to the serial console.
//
// Buy this module: https://shillehtek.com/products/hmc5883l-gy-273-magnetometer-compass-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hmc5883l-gy-273-magnetometer-compass-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HMC5883L (GY-273) Compass - ESP32 Example
// SDA -> GPIO 21, SCL -> GPIO 22, VCC -> 3V3, GND -> GND
// Library: "Adafruit HMC5883 Unified" (+ Adafruit Unified Sensor)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);   // SDA, SCL

  if (!mag.begin()) {
    Serial.println("HMC5883L not found at 0x1E - check wiring.");
    while (1) delay(10);
  }
  Serial.println("Compass ready - rotate the board slowly.");
}

void loop() {
  sensors_event_t event;
  mag.getEvent(&event);

  float heading = atan2(event.magnetic.y, event.magnetic.x);
  if (heading < 0) heading += 2 * PI;

  Serial.printf("X: %.1f uT  Y: %.1f uT  |  Heading: %.1f deg\n",
                event.magnetic.x, event.magnetic.y,
                heading * 180 / PI);
  delay(500);
}
