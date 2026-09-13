// Reads temperature from a DS18B20 probe and toggles a relay to maintain a target water temperature using a hysteresis band while printing temperature and state to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ds18b20-sous-vide-controller
// Parts used: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <OneWire.h>
#include <DallasTemperature.h>

const int PROBE = 2;
const int RELAY = 3;
const float TARGET = 54.4;     // target water temp (steak medium-rare)
const float HYSTERESIS = 0.3;  // +/- band

OneWire bus(PROBE);
DallasTemperature sensors(&bus);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  sensors.begin();
  sensors.setResolution(12);   // 12-bit = 0.0625C resolution
}

void loop() {
  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);
  Serial.print("Water: "); Serial.print(t, 2); Serial.print(" C  ");

  if (t < TARGET - HYSTERESIS) {
    digitalWrite(RELAY, HIGH);   // heater ON
    Serial.println("HEATING");
  } else if (t > TARGET + HYSTERESIS) {
    digitalWrite(RELAY, LOW);    // heater OFF
    Serial.println("IDLE");
  }
  delay(1000);
}
