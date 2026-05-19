// AT-command passthrough: puts the HC-05 into AT mode (requires the KEY/EN pin high) and forwards AT commands between the Arduino Serial Monitor and the module at 38400 baud.
//
// Buy this module: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-05-6pin-bluetooth-module-no-button-manual
// More examples: https://github.com/shillehtek/examples
//

// Configure HC-05 with AT commands
// 1. Wire EN/Key pin HIGH (3.3V) BEFORE powering the module
// 2. The LED should blink slowly (~2 Hz) instead of fast
// 3. Open Serial Monitor at 38400 baud, "Both NL & CR"
// 4. Type AT and you should see OK
//
// Common commands:
//   AT+NAME=MyHC05         (set device name)
//   AT+PSWD="2580"         (set pairing PIN)
//   AT+UART=115200,0,0     (change baud rate)
//   AT+ROLE=0              (slave) or AT+ROLE=1 (master)

#include <SoftwareSerial.h>
SoftwareSerial bt(2, 3);

void setup() {
  Serial.begin(38400);
  bt.begin(38400);
}

void loop() {
  if (bt.available()) Serial.write(bt.read());
  if (Serial.available()) bt.write(Serial.read());
}
