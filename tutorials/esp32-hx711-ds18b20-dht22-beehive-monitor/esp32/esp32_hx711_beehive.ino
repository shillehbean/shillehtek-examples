// Reads weight from an HX711 load cell, temperature from a DS18B20, and temperature/humidity from a DHT22 on an ESP32, then prints the values to Serial (with a placeholder to push to a server).
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-hx711-ds18b20-dht22-beehive-monitor
// Parts used: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
//             https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <HX711.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
HX711 scale;
OneWire bus(4); DallasTemperature ds(&bus);
DHT dht(5, DHT22);
const float CAL = 420.0;   // calibrate this for your load cell
void setup() {
  Serial.begin(115200);
  WiFi.begin("SSID","PASS");
  scale.begin(16, 17); scale.set_scale(CAL); scale.tare();
  ds.begin(); dht.begin();
}
void loop() {
  float w = scale.get_units(10);
  ds.requestTemperatures();
  float internalT = ds.getTempCByIndex(0);
  float ambientT = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.printf("kg=%.2f intT=%.1fC ambT=%.1fC RH=%.0f%%\n", w/1000.0, internalT, ambientT, h);
  // ...push to ThingSpeak / your own server every 5 minutes
  delay(300000);
}
