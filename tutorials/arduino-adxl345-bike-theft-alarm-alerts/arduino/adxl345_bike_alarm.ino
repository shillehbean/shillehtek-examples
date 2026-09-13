// Reads acceleration from an ADXL345, compares magnitude to a baseline, triggers a piezo buzzer and sends a Bluetooth alert when movement exceeds a threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-adxl345-bike-theft-alarm-alerts
// Parts used: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
Adafruit_ADXL345_Unified accel(12345);
SoftwareSerial bt(2,3);
const int BUZZ = 8;
const float THRESHOLD = 1.5; // m/s² of additional shake
float baseline = 0;
void setup() {
  bt.begin(9600);
  accel.begin();
  pinMode(BUZZ, OUTPUT);
  sensors_event_t e; accel.getEvent(&e);
  baseline = sqrt(e.acceleration.x*e.acceleration.x +
                  e.acceleration.y*e.acceleration.y +
                  e.acceleration.z*e.acceleration.z);
}
void loop() {
  sensors_event_t e; accel.getEvent(&e);
  float mag = sqrt(e.acceleration.x*e.acceleration.x +
                   e.acceleration.y*e.acceleration.y +
                   e.acceleration.z*e.acceleration.z);
  if (abs(mag - baseline) > THRESHOLD) {
    tone(BUZZ, 2000, 500);
    bt.println("ALARM! Movement detected.");
    delay(2000);
  }
  delay(50);
}
