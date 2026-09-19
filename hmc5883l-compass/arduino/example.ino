// Arduino sketch using the Adafruit HMC5883 Unified library to read magnetic field vectors and print a computed compass heading (in degrees) over Serial.
//
// Buy this module: https://shillehtek.com/products/hmc5883l-gy-273-magnetometer-compass-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hmc5883l-gy-273-magnetometer-compass-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HMC5883L (GY-273) Compass - Arduino Example
// SDA -> A4, SCL -> A5, VCC -> 5V, GND -> GND
// Library: "Adafruit HMC5883 Unified" (+ Adafruit Unified Sensor)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
  Serial.begin(9600);

  if (!mag.begin()) {
    Serial.println("HMC5883L not found at 0x1E - check wiring.");
    Serial.println("(If an I2C scan shows 0x0D, you have a QMC5883L.)");
    while (1);
  }
  Serial.println("Compass ready - rotate the board slowly.");
}

void loop() {
  sensors_event_t event;
  mag.getEvent(&event);

  // Heading from the horizontal components (board held flat)
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  // Add your local magnetic declination here (radians)
  // Example: +3 degrees = 0.052 rad
  // heading += 0.052;

  if (heading < 0) heading += 2 * PI;
  float degrees = heading * 180 / PI;

  Serial.print("X: ");
  Serial.print(event.magnetic.x);
  Serial.print(" uT  Y: ");
  Serial.print(event.magnetic.y);
  Serial.print(" uT  |  Heading: ");
  Serial.print(degrees, 1);
  Serial.println(" deg");

  delay(500);
}
