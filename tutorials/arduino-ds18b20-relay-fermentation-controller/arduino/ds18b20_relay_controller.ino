// Reads temperature from a DS18B20 sensor and switches a relay on/off to maintain a target incubation temperature with a hysteresis band, while printing status to serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ds18b20-relay-fermentation-controller
// Parts used: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <OneWire.h>
#include <DallasTemperature.h>
const int PROBE = 2, RELAY = 3;
const float TARGET = 44.0;   // yogurt incubation temp
const float BAND = 0.5;
OneWire bus(PROBE); DallasTemperature ds(&bus);
void setup() {
  Serial.begin(9600); ds.begin();
  pinMode(RELAY, OUTPUT);
}
void loop() {
  ds.requestTemperatures();
  float t = ds.getTempCByIndex(0);
  digitalWrite(RELAY, t < (TARGET - BAND) ? HIGH : LOW);
  Serial.printf("T=%.2f C  Heat: %s\n", t,
    (t < TARGET - BAND) ? "ON" : "OFF");
  delay(1000);
}
