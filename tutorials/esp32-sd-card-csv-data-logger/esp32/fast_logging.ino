// Example showing how to open a log file once for faster repeated writes and flush to the SD card periodically to reduce wear and improve performance.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

File logFile;
void setup() {
  // ...
  logFile = SD.open("/fast.csv", FILE_APPEND);
}
void loop() {
  logFile.print(micros());
  logFile.print(",");
  logFile.println(analogRead(A0));
  static int count = 0;
  if (++count % 100 == 0) logFile.flush();   // flush every 100 rows
}
