// Sweeps a servo across a 60° arc while reading distances from a VL53L1X sensor, outputs comma-separated angle,distance over serial, and activates a buzzer when distance is below a threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-vl53l1x-servo-radar-scanner
// Parts used: https://shillehtek.com/products/vl53l1x-tof-sensor-4m-pre-soldered-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <VL53L1X.h>
#include <Servo.h>

VL53L1X sensor;
Servo sweep;

const int SERVO_PIN   = 9;
const int BUZZER_PIN  = 8;
const int CENTER      = 90;     // sweep +/-30 degrees around center
const int HALF_ARC    = 30;
const int THRESHOLD   = 2000;   // alert distance in mm (2 m)

int angle = CENTER - HALF_ARC;
int dir   = 1;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.setTimeout(500);
  sensor.init();
  sensor.setDistanceMode(VL53L1X::Long);      // 4 m mode
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);

  sweep.attach(SERVO_PIN);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  sweep.write(angle);
  delay(60);                                  // let the servo settle

  int mm = sensor.read();                     // distance at this angle
  Serial.print(angle); Serial.print(",");
  Serial.println(mm);                         // "angle,distance" for plotting

  digitalWrite(BUZZER_PIN, (mm > 0 && mm < THRESHOLD) ? HIGH : LOW);

  angle += dir * 2;                           // 2-degree steps
  if (angle >= CENTER + HALF_ARC || angle <= CENTER - HALF_ARC) dir = -dir;
}
