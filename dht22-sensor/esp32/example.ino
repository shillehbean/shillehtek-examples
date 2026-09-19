// ESP32 Arduino sketch using the Adafruit DHT library to read temperature and humidity from a DHT22 on GPIO4 and print the results to Serial at 115200 baud every ~2 seconds.
//
// Buy this module: https://shillehtek.com/products/shillehtek-dht22-with-cables
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dht22-digital-temperature-and-humidity-sensor-module-with-cable
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// DHT22 - ESP32 Arduino Example
// Requires Adafruit DHT sensor library

#include <DHT.h>

#define DHTPIN 4          // DATA pin connected to GPIO 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT22 read failed");
    return;
  }
  Serial.printf("Temp: %.1f C  Humidity: %.1f%%\n", t, h);
}
