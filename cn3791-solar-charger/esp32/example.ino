// Samples and averages the battery voltage on an ESP32, prints it, and puts the board into deep sleep for one hour if the voltage is below the configured low-battery threshold.
//
// Buy this module: https://shillehtek.com/products/Battery
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cn3791-6v-mppt-solar-charger-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// CN3791 + ESP32 - reads battery, sleeps if low.
// Wire BAT through 100k/100k divider to GPIO34.

const int BAT_PIN = 34;
const float VREF = 3.3;
const float DIVIDER_RATIO = 2.0;
const float LOW_BAT_SLEEP = 3.2; // volts - go to sleep below this
const uint64_t SLEEP_US = 60ULL * 60ULL * 1000000ULL; // 1 hour

float readBatteryVoltage() {
  // Average 16 samples for stability
  uint32_t sum = 0;
  for (int i = 0; i < 16; i++) {
    sum += analogRead(BAT_PIN);
    delay(2);
  }
  float raw = sum / 16.0;
  float vPin = (raw / 4095.0) * VREF;
  return vPin * DIVIDER_RATIO;
}

void setup() {
  Serial.begin(115200);
  delay(200);

  float vBat = readBatteryVoltage();
  Serial.printf("Battery: %.2f V\n", vBat);

  if (vBat < LOW_BAT_SLEEP) {
    Serial.println("Low battery - deep sleep 1h");
    esp_sleep_enable_timer_wakeup(SLEEP_US);
    esp_deep_sleep_start();
  }

  // Otherwise do normal work: read sensors, post data, etc.
  Serial.println("Battery OK - running normally");
}

void loop() {
  delay(5000);
}
