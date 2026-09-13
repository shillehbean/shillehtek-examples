// Two minimal Arduino sketches: one using the MAX30100_PulseOximeter library to initialize the MAX30100 and print heart rate / beat events, and one using the MAX30105 library to initialize the MAX30102, read IR values, and detect beats.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-max30102-vs-max30100-choose-best-sensor
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
//             https://shillehtek.com/products/tp4056-1a-lipo-battery-charging-board-type-c-with-current-protection
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MAX30100
#include <MAX30100_PulseOximeter.h>
PulseOximeter pox;
void setup() {
  Serial.begin(115200);
  pox.begin();
  pox.setOnBeatDetectedCallback([](){ Serial.println("beat"); });
}
void loop() {
  pox.update();
  Serial.println(pox.getHeartRate());
  delay(500);
}

// MAX30102
#include <MAX30105.h>
#include <heartRate.h>
MAX30105 sensor;
void setup() {
  Serial.begin(115200);
  sensor.begin();
  sensor.setup();
}
void loop() {
  long ir = sensor.getIR();
  if (checkForBeat(ir)) Serial.println("beat");
}
