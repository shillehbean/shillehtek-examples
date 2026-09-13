// Initializes the DS3231 realtime clock and sets its time to the sketch compile time.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ds3231-rtc-alarm-clock-oled
// Parts used: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;
void setup() {
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   // set to compile time
}
void loop() {}
