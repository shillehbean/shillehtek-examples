// Basic SoftwareSerial echo: forwards text from a paired phone to the Arduino Serial Monitor and echos the same text back to the phone at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-05-6pin-bluetooth-module-no-button-manual
// More examples: https://github.com/shillehtek/examples
//

// HC-05 Bluetooth - Arduino Echo Example
// Pair from your phone with "Serial Bluetooth Terminal" app
// Default PIN: 1234 (or 0000)

#include <SoftwareSerial.h>

// HC-05 TX -> D2, HC-05 RX (via divider) -> D3
SoftwareSerial bt(2, 3);

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  Serial.println("HC-05 ready. Pair and send text.");
}

void loop() {
  // Phone -> Arduino
  if (bt.available()) {
    String msg = bt.readString();
    Serial.print("Got: ");
    Serial.println(msg);
    bt.print("Echo: ");
    bt.println(msg);
  }
  // Arduino -> phone
  if (Serial.available()) {
    bt.write(Serial.read());
  }
}
