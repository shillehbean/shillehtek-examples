// Arduino sketch that uses the Adafruit DHT library to read temperature and humidity from a DHT22 on digital pin 2 and print the values over Serial every ~2 seconds.
//
// Buy this module: https://shillehtek.com/products/shillehtek-dht22-with-cables
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dht22-digital-temperature-and-humidity-sensor-module-with-cable
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// DHT22 Temperature & Humidity Sensor - Arduino Example
// Requires Adafruit DHT sensor library

#include <DHT.h>

#define DHTPIN 2          // DATA pin connected to digital 2
#define DHTTYPE DHT22     // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 starting...");
  dht.begin();
}

void loop() {
  delay(2000);  // DHT22 needs ~2s between readings

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
}
