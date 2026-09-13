// Example Arduino snippets showing how to read temperature from a thermistor (analog), DHT22, DS18B20 (1-Wire), BME280 (I2C), and MLX90614 (I2C non-contact) using common libraries.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-temperature-sensors-selection-guide
// Parts used: https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
//             https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Thermistor (analog)
int adc = analogRead(A0);
float R = 10000.0 * (1023.0 / adc - 1);  // for 10k NTC + 10k pull-up
// Steinhart-Hart for proper temp conversion

// DHT22 (single-wire)
#include <DHT.h>
DHT dht(2, DHT22); dht.begin();
float t = dht.readTemperature();

// DS18B20 (1-Wire)
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire b(2); DallasTemperature ds(&b);
ds.begin(); ds.requestTemperatures();
float t = ds.getTempCByIndex(0);

// BME280 (I2C)
#include <Adafruit_BME280.h>
Adafruit_BME280 bme; bme.begin(0x76);
float t = bme.readTemperature();

// MLX90614 (I2C non-contact)
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx; mlx.begin();
float t = mlx.readObjectTempC();
