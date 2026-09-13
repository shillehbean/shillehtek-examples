// Reads GPS data from a NEO-6M and IMU data from an MPU6050, then logs timestamped CSV rows to a microSD card.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mpu6050-neo6m-vehicle-data-logger
// Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
//             https://shillehtek.com/products/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
SoftwareSerial gpsSer(4, 3);
File log;
void setup() {
  Serial.begin(9600); gpsSer.begin(9600);
  mpu.begin(); SD.begin(10);
  log = SD.open("trip.csv", FILE_WRITE);
  log.println("time,lat,lng,speed_kmh,ax,ay,az,gz");
}
void loop() {
  while (gpsSer.available()) gps.encode(gpsSer.read());
  if (gps.location.isUpdated()) {
    sensors_event_t a, g, t; mpu.getEvent(&a, &g, &t);
    log.printf("%lu,%.6f,%.6f,%.1f,%.2f,%.2f,%.2f,%.2f\n",
      millis(), gps.location.lat(), gps.location.lng(), gps.speed.kmph(),
      a.acceleration.x, a.acceleration.y, a.acceleration.z, g.gyro.z);
    log.flush();
  }
}
