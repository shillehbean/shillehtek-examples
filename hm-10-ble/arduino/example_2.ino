// Listens for single-character commands ('1' to turn on, '0' to turn off) sent over BLE and toggles an Arduino LED, demonstrating remote control from a phone app.
//
// Buy this module: https://shillehtek.com/products/hm-10-bluetooth-4-0-ble-cc2541-master-slave-module-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hm-10-bluetooth-4-0-ble-cc2541-master-slave-module-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// HM-10 - Toggle LED from a phone app (LightBlue, BLE Scanner, etc.)
// Send "1" to turn on, "0" to turn off.

#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3);
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  bt.begin(9600);
}

void loop() {
  if (bt.available()) {
    char c = bt.read();
    if (c == '1') digitalWrite(ledPin, HIGH);
    if (c == '0') digitalWrite(ledPin, LOW);
  }
}
