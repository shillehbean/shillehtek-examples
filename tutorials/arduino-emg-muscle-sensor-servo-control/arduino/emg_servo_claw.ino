// Reads the EMG sensor on A0, calibrates a baseline, prints readings over Serial, and moves a servo on pin 9 to open or closed positions when the signal exceeds a configurable threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-emg-muscle-sensor-servo-control
// Parts used: https://shillehtek.com/products/emg-muscle-signal-sensor-module-kit-for-arduino-robotics
//             https://shillehtek.com/products/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>
const int EMG = A0;
Servo claw;
const int CLOSED = 0, OPEN = 90;
const int THRESHOLD = 350;   // tune for your skin
int baseline = 0;
void setup() {
  Serial.begin(9600);
  claw.attach(9);
  long sum = 0;
  for (int i = 0; i < 100; i++) { sum += analogRead(EMG); delay(10); }
  baseline = sum / 100;
}
void loop() {
  int v = analogRead(EMG);
  Serial.println(v);
  int diff = abs(v - baseline);
  claw.write(diff > THRESHOLD ? CLOSED : OPEN);
  delay(20);
}
