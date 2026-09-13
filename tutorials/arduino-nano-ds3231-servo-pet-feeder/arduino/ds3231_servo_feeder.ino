// Reads time from a DS3231 RTC and dispenses food by moving a servo and sounding a buzzer at configured hours; also allows manual dispensing via a button.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds3231-servo-pet-feeder
// Parts used: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
RTC_DS3231 rtc; Servo gate;
const int BUZZ=8, BTN=2;
const int FEED_HOURS[] = {7, 18};   // 7am + 6pm
int lastFed = -1;
void dispense() {
  tone(BUZZ, 880, 300); delay(400); noTone(BUZZ);
  gate.write(90); delay(800);
  gate.write(0);  delay(800);
}
void setup() {
  Wire.begin(); rtc.begin();
  pinMode(BTN, INPUT_PULLUP);
  pinMode(BUZZ, OUTPUT);
  gate.attach(9); gate.write(0);
}
void loop() {
  DateTime now = rtc.now();
  for (int h : FEED_HOURS) {
    if (now.hour() == h && now.minute() == 0 && lastFed != h) {
      dispense();
      lastFed = h;
    }
  }
  if (digitalRead(BTN) == LOW) dispense();
  delay(500);
}
