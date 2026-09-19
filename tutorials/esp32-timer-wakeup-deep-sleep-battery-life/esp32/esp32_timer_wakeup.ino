// Sets up an ESP32 deep-sleep timer wake-up loop: it counts boots in RTC memory, prints the wake reason over serial, blinks the onboard LED, then enables a timer wakeup and enters deep sleep.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-timer-wakeup-deep-sleep-battery-life
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define uS_TO_S 1000000ULL
const int SLEEP_S = 10;                 // seconds asleep between wake-ups
const int LED = 2;                      // onboard LED on most ESP32 dev boards

RTC_DATA_ATTR int bootCount = 0;        // lives in RTC memory, survives deep sleep

void printWakeReason() {
  esp_sleep_wakeup_cause_t r = esp_sleep_get_wakeup_cause();
  switch (r) {
    case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Woke up: timer");        break;
    case ESP_SLEEP_WAKEUP_EXT0:  Serial.println("Woke up: external pin"); break;
    default:                     Serial.printf("Power-on or reset (%d)\n", r); break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);                           // give the serial monitor a moment

  bootCount++;
  Serial.printf("Boot #%d\n", bootCount);
  printWakeReason();

  pinMode(LED, OUTPUT);                 // "I'm awake" blink x3
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED, HIGH); delay(150);
    digitalWrite(LED, LOW);  delay(150);
  }

  // --- do the real work here: read a sensor, send a packet, log a value ---

  esp_sleep_enable_timer_wakeup(SLEEP_S * uS_TO_S);
  Serial.printf("Sleeping for %d s...\n", SLEEP_S);
  Serial.flush();                       // make sure the text leaves before power drops
  esp_deep_sleep_start();
}

void loop() {
  // never reached: deep sleep resets the chip and setup() runs again
}
