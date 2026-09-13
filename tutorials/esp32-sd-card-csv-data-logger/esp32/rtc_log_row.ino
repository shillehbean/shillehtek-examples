// Helper code that uses an attached DS3231 RTC to format a timestamped CSV row and append it to the log file on the SD card.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <RTClib.h>
RTC_DS3231 rtc;

void logRow(float t, float h) {
  DateTime now = rtc.now();
  char buf[24];
  sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  File f = SD.open(LOG_FILE, FILE_APPEND);
  f.print(buf); f.print(",");
  f.print(t, 1); f.print(",");
  f.println(h, 1);
  f.close();
}
