// Uses the Adafruit ADXL345 Arduino library over I2C to initialize the sensor, set the range to ±4g, and print X/Y/Z acceleration in m/s² every 200 ms.
//
// Buy this module: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

// ADXL345 3-Axis Accelerometer - Arduino I2C Example
// Library: Adafruit ADXL345 (install via Library Manager)
// Wiring: SDA -> A4, SCL -> A5, 5V -> 5V, GND -> GND, CS -> 3.3V

#include 
#include 
#include 

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  Serial.println("ADXL345 starting...");

  if (!accel.begin()) {
    Serial.println("No ADXL345 detected. Check wiring and CS pin.");
    while (1);
  }

  accel.setRange(ADXL345_RANGE_4_G);
  Serial.println("ADXL345 ready.");
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" m/s^2  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" m/s^2  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.println(" m/s^2");

  delay(200);
}
