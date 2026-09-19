// Arduino sketch that reads time from a DS3231 RTC and displays hours (5 LEDs) and minutes (6 LEDs) in binary, with a heartbeat LED toggling each second.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds3231-binary-led-clock
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;

const int HOUR_PINS[5] = {2, 3, 4, 5, 6};        // place values 16 8 4 2 1
const int MIN_PINS[6]  = {7, 8, 9, 10, 11, 12};  // place values 32 16 8 4 2 1
const int TICK = 13;                             // blinks once a second

void showBits(const int* pins, int n, int value) {   // MSB on the left-most LED
  for (int i = 0; i < n; i++) digitalWrite(pins[i], (value >> (n - 1 - i)) & 1);
}

void setup() {
  for (int i = 0; i < 5; i++) pinMode(HOUR_PINS[i], OUTPUT);
  for (int i = 0; i < 6; i++) pinMode(MIN_PINS[i], OUTPUT);
  pinMode(TICK, OUTPUT);
  rtc.begin();
  if (rtc.lostPower()) {                                     // fresh module or dead cell:
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));          // set from the time this sketch was compiled
  }
  // to set the time by hand once, uncomment, upload, then comment out and upload again:
  // rtc.adjust(DateTime(2026, 9, 13, 21, 45, 0));
}

void loop() {
  DateTime now = rtc.now();
  showBits(HOUR_PINS, 5, now.hour());        // 0..23
  showBits(MIN_PINS, 6, now.minute());       // 0..59
  digitalWrite(TICK, now.second() % 2);      // heartbeat
  delay(200);
}
