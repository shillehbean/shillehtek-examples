// Use the Adafruit_BNO08x library on an ESP32 over I2C to enable the game rotation vector report and read orientation quaternions (converted to angles).
//
// Buy this module: https://shillehtek.com/products/bno085-imu-pre-soldered-orientation-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bno085-imu-pre-soldered-orientation-sensor-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BNO085 (GY-BNO08X) on an ESP32 over I2C - quaternion to yaw / pitch / roll
// Library Manager: install "Adafruit BNO08x" (it pulls in Adafruit BusIO and Unified Sensor)
// Wiring: VCC -> 3V3, GND -> GND, SDA -> GPIO 21, SCL -> GPIO 22 (PS0 and PS1 left open)
#include <Adafruit_BNO08x.h>

#define BNO08X_RESET -1            // RST pin not wired
Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setReports() {
  // Game rotation vector: smooth orientation from the accelerometer and gyroscope
  if (!bno08x.enableReport(SH2_GAME_ROTATION_VECTOR, 20000)) {   // one report every 20 ms
    Serial.println("Could not enable the game rotation vector");
  }
}

void setup() {
  Serial.begin(115200);
  // This board style normally answers at 0x4B; it moves to 0x4A when ADD is tied to GND
  if (!bno08x.begin_I2C(0x4B) && !bno08x.begin_I2C(0x4A)) {
    Serial.println("BNO085 not found - check wiring and 3.3 V power");
    while (true) { delay(1000); }
  }
  setReports();
}

void loop() {
  if (bno08x.wasReset()) setReports();            // turn the report back on after a reset
  if (!bno08x.getSensorEvent(&sensorValue)) return;
  if (sensorValue.sensorId != SH2_GAME_ROTATION_VECTOR) return;

  float qr = sensorValue.un.gameRotationVector.real;
  float qi = sensorValue.un.gameRotationVector.i;
  float qj = sensorValue.un.gameRotationVector.j;
  float qk = sensorValue.un.gameRotationVector.k;

  float yaw   = atan2(2.0 * (qi * qj + qk * qr), 1.0 - 2.0 * (qj * qj + qk * qk)) * RAD_TO_DEG;
  float pitch = asin(constrain(2.0 * (qj * qr - qi * qk), -1.0, 1.0)) * RAD_TO_DEG;
  float roll  = atan2(2.0 * (qj * qk + qi * qr), 1.0 - 2.0 * (qi * qi + qj * qj)) * RAD_TO_DEG;

  Serial.print("Yaw: ");
  Serial.print(yaw, 1);
  Serial.print("   Pitch: ");
  Serial.print(pitch, 1);
  Serial.print("   Roll: ");
  Serial.println(roll, 1);
}
