// Reads temperature and humidity from a DHT22 sensor using the Adafruit DHT library and prints values to Serial every 2 seconds.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-dht22-log-temp-humidity-serial
// Parts used: https://shillehtek.com/products/shillehtek-dht22-with-cables
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("DHT read failed"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h, 1);
  Serial.print(F("%  Temp: "));
  Serial.print(t, 1);
  Serial.println(F(" C"));
}
