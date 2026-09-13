// Arduino sketch that uses a DS3231 RTC to trigger servo indexing and a buzzer at scheduled hours, with a button input for interactions.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds3231-pill-dispenser-alerts
// Parts used: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
RTC_DS3231 rtc; Servo carousel;
const int BUZZ = 8, BTN = 2;
// Schedule: 7am, 1pm, 7pm
const int HOURS[] = {7, 13, 19};
int slot = 0;
int lastDispensed = -1;

void dispense() {
  tone(BUZZ, 880, 300); delay(400); noTone(BUZZ);
  carousel.write(slot * 51);   // 51° per slot for 7 slots
  slot = (slot + 1) % 7;
}

void setup() {
  Wire.begin(); rtc.begin();
  carousel.attach(9); carousel.write(0);
  pinMode(BUZZ, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  DateTime now = rtc.now();
  for (int h : HOURS) {
    if (now.hour() == h && now.minute() == 0 && lastDispensed != h) {
      dispense();
      lastDispensed = h;
    }
  }
  // Audible reminder every 5 min until button pressed
  delay(500);
}
