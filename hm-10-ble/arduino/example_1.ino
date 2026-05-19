// Provides a serial bridge between the PC Serial Monitor and the HM-10 so you can type AT commands from your computer and see the module's responses.
//
// Buy this module: https://shillehtek.com/products/hm-10-bluetooth-4-0-ble-cc2541-master-slave-module-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hm-10-bluetooth-4-0-ble-cc2541-master-slave-module-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// HM-10 Bluetooth Bridge - Arduino Example
// Connect HM-10 RX -> D3, TX -> D2 (via voltage divider for RX)
// Send AT commands from Serial Monitor at 9600 baud, "No line ending"

#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3);   // RX, TX

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  Serial.println("Type AT in Serial Monitor (No line ending). Should reply OK.");
}

void loop() {
  if (bt.available())     Serial.write(bt.read());
  if (Serial.available()) bt.write(Serial.read());
}
