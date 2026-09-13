// Reads mains presence on an analog pin, measures battery voltage and current via an INA219, prints values over serial, and toggles a GPIO to signal the Raspberry Pi to shut down when battery voltage is low.
//
// Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-tp4056-ina219-mini-ups-backup
// Parts used: https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
//             https://shillehtek.com/products/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam
//             https://shillehtek.com/products/mt3608-dc-dc-step-up-boost-converter-2a-adjustable-power-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina;
const int MAINS_SENSE = A0;
const int LOW_BATT_PIN = 8;   // signal Pi to shut down

void setup() {
  Serial.begin(9600);
  ina.begin();
  pinMode(LOW_BATT_PIN, OUTPUT);
}

void loop() {
  int mainsRaw = analogRead(MAINS_SENSE);
  float mainsV = mainsRaw * (5.0 / 1023.0) * 2;   // divider ratio
  float battV = ina.getBusVoltage_V();
  float loadMA = ina.getCurrent_mA();

  Serial.printf("Mains: %.1fV  Batt: %.2fV  Load: %.0fmA\n", mainsV, battV, loadMA);

  // Tell the Pi to shut down gracefully if battery drops below 3.3V
  digitalWrite(LOW_BATT_PIN, battV < 3.3 ? HIGH : LOW);

  delay(2000);
}
