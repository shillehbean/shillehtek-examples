// ESP32 Arduino sketch that reads a DHT22 sensor and appends temperature and humidity rows to /log.csv on the SD card, creating a header if needed.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <SD.h>
#include <DHT.h>

DHT dht(4, DHT22);
const int SD_CS = 5;
const char* LOG_FILE = "/log.csv";

void setup() {
  Serial.begin(115200);
  dht.begin();
  if (!SD.begin(SD_CS)) {
    Serial.println("SD failed");
    while (1);
  }
  // Write header if file doesn't exist
  if (!SD.exists(LOG_FILE)) {
    File f = SD.open(LOG_FILE, FILE_WRITE);
    f.println("millis,temp_c,humidity_pct");
    f.close();
  }
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  File f = SD.open(LOG_FILE, FILE_APPEND);
  f.print(millis());
  f.print(","); f.print(t, 1);
  f.print(","); f.println(h, 1);
  f.close();
  delay(5000);
}
