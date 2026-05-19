// Creates a bidirectional serial passthrough so you can type AT commands to the ESP-01 from the Arduino Serial Monitor and see responses.
//
// Buy this module: https://shillehtek.com/products/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp8266-esp-01-serial-wifi-module-1mb-wireless-transceiver-iot-manual
// More examples: https://github.com/shillehtek/examples
//

// Arduino - manually talk to the ESP-01 from the Serial Monitor
// Open Serial Monitor at 9600, set "Both NL & CR" so AT commands end correctly
// Try: AT, AT+GMR (firmware version), AT+CWLAP (scan APs)

#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);   // RX = D2, TX = D3 (through divider)

void setup() {
  Serial.begin(9600);
  esp.begin(9600);          // some AT firmwares default to 115200; try both
  Serial.println("ESP-01 AT pass-through. Type commands above.");
}

void loop() {
  while (esp.available())    Serial.write(esp.read());
  while (Serial.available()) esp.write(Serial.read());
}
