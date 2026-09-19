// Configure a touch pad interrupt and enable touchpad wake from deep sleep; blink the output on boot then enter deep sleep to wait for a touch to wake the ESP32.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-capacitive-touch-toggle-wake-deep-sleep
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define THRESHOLD 40                        // a bit above your "touched" reading
void onTouch() {}                           // required, can be empty

void setup() {
  pinMode(2, OUTPUT);
  for (int i = 0; i < 3; i++) { digitalWrite(2, HIGH); delay(100); digitalWrite(2, LOW); delay(100); }
  touchAttachInterrupt(T0, onTouch, THRESHOLD);
  esp_sleep_enable_touchpad_wakeup();
  esp_deep_sleep_start();                   // ~10 uA until the pad is touched
}
void loop() {}
