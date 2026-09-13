// Use SoftwareSerial to communicate with an HM-10 BLE module, forward data between BLE and USB serial, and toggle the onboard LED when receiving '1' or '0' commands.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-hm10-ble-control-from-iphone
// Parts used: https://shillehtek.com/products/hm-10-bluetooth-4-0-ble-cc2541-master-slave-module-for-arduino
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>

SoftwareSerial ble(2, 3);   // RX, TX
const int LED = 13;

void setup() {
  Serial.begin(9600);
  ble.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  while (ble.available()) {
    char c = ble.read();
    Serial.write(c);
    if (c == '1') digitalWrite(LED, HIGH);
    if (c == '0') digitalWrite(LED, LOW);
  }
  while (Serial.available()) ble.write(Serial.read());
}
