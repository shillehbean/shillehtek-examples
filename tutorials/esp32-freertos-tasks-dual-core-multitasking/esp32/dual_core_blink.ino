// Creates two FreeRTOS tasks pinned to separate cores that blink two GPIO pins at different rates.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-freertos-tasks-dual-core-multitasking
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void blinkA(void*) {                        // runs forever on core 0
  pinMode(16, OUTPUT);
  for (;;) { digitalWrite(16, !digitalRead(16)); vTaskDelay(pdMS_TO_TICKS(500)); }
}
void blinkB(void*) {                        // runs forever on core 1
  pinMode(17, OUTPUT);
  for (;;) { digitalWrite(17, !digitalRead(17)); vTaskDelay(pdMS_TO_TICKS(130)); }
}

void setup() {
  Serial.begin(115200);
  //                 function, name,   stack, arg,  priority, handle, core
  xTaskCreatePinnedToCore(blinkA, "blinkA", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(blinkB, "blinkB", 2048, NULL, 1, NULL, 1);
}
void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }   // loop() is itself a task; let it rest
