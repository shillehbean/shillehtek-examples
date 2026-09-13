// Arduino sketch that reads time and temperature from a DS3231 RTC and displays the time on a TM1637 4-digit display, briefly showing temperature periodically; includes an optional RTC time-set line.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds3231-tm1637-drift-free-alarm-clock
// Parts used: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <RtcDS3231.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3
TM1637Display disp(CLK, DIO);
RtcDS3231<TwoWire> rtc(Wire);

void setup() {
  disp.setBrightness(0x0a);
  rtc.Begin();
  // Uncomment to set time once:
  // rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop() {
  RtcDateTime now = rtc.GetDateTime();
  int hhmm = now.Hour() * 100 + now.Minute();
  disp.showNumberDecEx(hhmm, 0x40, true);   // colon ON

  if ((millis() / 5000) % 2 == 0) {
    // every 10 seconds, briefly show temp
    int tempC = rtc.GetTemperature().AsFloatDegC();
    disp.showNumberDecEx(tempC * 100 + 0, 0x80);
    delay(2000);
  }
  delay(500);
}
