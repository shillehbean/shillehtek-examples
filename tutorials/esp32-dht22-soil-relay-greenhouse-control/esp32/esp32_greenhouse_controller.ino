// Reads DHT22 temperature/humidity and an analog soil moisture sensor, connects to Wi-Fi, controls pump and fan relays based on thresholds, and logs values to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-dht22-soil-relay-greenhouse-control
// Parts used: https://shillehtek.com/products/shillehtek-dht22-with-cables
//             https://shillehtek.com/products/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit
//             https://shillehtek.com/products/2-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT22
#define SOIL_PIN 36
#define PUMP 26
#define FAN 27
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(PUMP, OUTPUT); pinMode(FAN, OUTPUT);
  WiFi.begin("YOUR_SSID","YOUR_PASS");
}
void loop() {
  float t = dht.readTemperature(), h = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);
  // Lower soil reading = drier. Threshold ~2500/4095 for "dry".
  digitalWrite(PUMP, (soil > 2500) ? HIGH : LOW);
  digitalWrite(FAN,  (t > 30.0)   ? HIGH : LOW);
  Serial.printf("T=%.1fC H=%.1f%% soil=%d\n", t, h, soil);
  delay(5000);
}
