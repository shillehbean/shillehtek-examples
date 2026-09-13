// Snippet that generates a daily log filename (e.g., /log_YYYYMMDD.csv) using the current date from the RTC.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

char filename[24];
DateTime now = rtc.now();
sprintf(filename, "/log_%04d%02d%02d.csv",
        now.year(), now.month(), now.day());
