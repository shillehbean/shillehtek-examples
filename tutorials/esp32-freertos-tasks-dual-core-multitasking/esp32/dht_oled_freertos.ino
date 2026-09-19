// Implements a FreeRTOS producer/consumer pattern where a sensor task reads DHT11 values and sends them over a queue to a display task that updates an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-freertos-tasks-dual-core-multitasking
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

DHT dht(4, DHT11);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
typedef struct { float t, h; unsigned long ms; } Reading;
QueueHandle_t q;

void sensorTask(void*) {                    // producer
  dht.begin();
  for (;;) {
    Reading r = { dht.readTemperature(), dht.readHumidity(), millis() };
    xQueueSend(q, &r, 0);                   // drop the reading if the queue is full
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void displayTask(void*) {                   // consumer
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  Reading r;
  for (;;) {
    if (xQueueReceive(q, &r, portMAX_DELAY)) {   // sleeps until a reading arrives
      oled.clearDisplay();
      oled.setTextSize(2); oled.setCursor(0, 0);  oled.printf("%.1f C", r.t);
      oled.setCursor(0, 24);                      oled.printf("%.0f %%", r.h);
      oled.setTextSize(1); oled.setCursor(0, 52); oled.printf("core %d  t=%lus", xPortGetCoreID(), r.ms / 1000);
      oled.display();
    }
  }
}

void setup() {
  Serial.begin(115200);
  q = xQueueCreate(5, sizeof(Reading));
  xTaskCreatePinnedToCore(sensorTask,  "sensor",  4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(displayTask, "display", 4096, NULL, 2, NULL, 0);   // higher priority
  // the two blink tasks from Step 2 can be created here as well
}
void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
