// Reads humidity and temperature from a DHT22 sensor and prints the values (Celsius and Fahrenheit) to the Serial Monitor every two seconds.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-dht22-temp-humidity-serial
// Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <DHT.h>
  
  #define DHTPIN 5      // D5 on ESP32 (GPIO5)
  #define DHTTYPE DHT22
  
  DHT dht(DHTPIN, DHTTYPE);
  
  void setup() {
    Serial.begin(115200);
    dht.begin();
  }
  
  void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();       // Celsius
    float f = dht.readTemperature(true);   // Fahrenheit
  
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("DHT22 read failed");
      delay(2000);
      return;
    }
  
    Serial.print("Humidity: ");
    Serial.print(h, 1);
    Serial.print("%  Temp: ");
    Serial.print(t, 1);
    Serial.print("C  ");
    Serial.print(f, 1);
    Serial.println("F");
  
    delay(2000);
  }
