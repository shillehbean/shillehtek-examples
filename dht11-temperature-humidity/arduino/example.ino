// Reads temperature and humidity from a DHT11 on digital pin 2 using the Adafruit DHT library and prints values to the Serial monitor every 2 seconds.
//
// Buy this module: https://shillehtek.com/products/shillehtek-dht11-with-cables
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/f
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// DHT11 - Arduino Example
// Library: DHT sensor library by Adafruit (Library Manager)

#include <DHT.h>

#define DHTPIN  2          // Digital pin 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);   // DHT11 needs 1+ second between reads

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT11!");
    return;
  }

  Serial.print("Humidity: "); Serial.print(h); Serial.print("%  ");
  Serial.print("Temp: ");     Serial.print(t); Serial.println(" C");
}
