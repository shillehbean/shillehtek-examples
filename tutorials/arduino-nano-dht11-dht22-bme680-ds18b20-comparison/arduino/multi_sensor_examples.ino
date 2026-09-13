// Minimal example snippets showing how to read temperature and humidity from DHT11/DHT22, DS18B20, and BME680 (using BSEC) on an Arduino Nano.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-dht11-dht22-bme680-ds18b20-comparison
// Parts used: https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
//             https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// DHT11/DHT22
#include <DHT.h>
DHT dht(2, DHT22);  // or DHT11
dht.begin();
float t = dht.readTemperature();
float h = dht.readHumidity();

// DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire bus(2);
DallasTemperature ds(&bus);
ds.begin();
ds.requestTemperatures();
float t = ds.getTempCByIndex(0);

// BME680 (with BSEC library)
#include <bsec.h>
Bsec iaq;
iaq.begin(BME68X_I2C_ADDR_HIGH, Wire);
iaq.run();
float t = iaq.temperature;
float gas = iaq.iaq;  // 0-500 index
