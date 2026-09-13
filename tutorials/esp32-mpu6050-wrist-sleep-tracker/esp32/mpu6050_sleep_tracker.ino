// Reads the MPU6050 accelerometer, computes the per-minute peak acceleration magnitude (activity level) minus gravity, and prints the 1-minute peak to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-mpu6050-wrist-sleep-tracker
// Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/esp32-c3-dev-board-4mb-wifi-presoldered
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;
unsigned long minuteStart = 0;
float minuteMax = 0;
void setup() {
  Serial.begin(115200);
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  minuteStart = millis();
}
void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  // Compute total acceleration magnitude minus gravity
  float mag = abs(sqrt(a.acceleration.x*a.acceleration.x +
                       a.acceleration.y*a.acceleration.y +
                       a.acceleration.z*a.acceleration.z) - 9.8);
  if (mag > minuteMax) minuteMax = mag;
  if (millis() - minuteStart >= 60000) {
    Serial.print("Activity (1min peak m/s^2): ");
    Serial.println(minuteMax, 2);
    // Store in EEPROM / push to server. Lower = deeper sleep.
    minuteMax = 0;
    minuteStart = millis();
  }
  delay(100);
}
