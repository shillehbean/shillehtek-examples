// ESP32 Arduino-framework snippet that checks an analog input and sends an HTTP POST notification to ntfy.sh when the reading exceeds a threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mq-2-gas-leak-alarm
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <HTTPClient.h>

void notify(const char* msg) {
  HTTPClient http;
  http.begin("https://ntfy.sh/my_gas_alarm_topic");
  http.addHeader("Title", "Gas Alarm");
  http.addHeader("Priority", "urgent");
  http.POST(msg);
  http.end();
}

void loop() {
  int v = analogRead(34);
  if (v > THRESHOLD) notify("Gas detected!");
  delay(2000);
}
