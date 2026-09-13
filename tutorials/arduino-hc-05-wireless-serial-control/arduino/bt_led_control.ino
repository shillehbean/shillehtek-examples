// Read newline-terminated text commands from the HC-05 and control the onboard LED (pin 13) with commands: "on", "off", and "status".
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hc-05-wireless-serial-control
// Parts used: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>

SoftwareSerial bt(2, 3);
const int LED = 13;
String line;

void setup() {
  pinMode(LED, OUTPUT);
  bt.begin(9600);
  Serial.begin(9600);
}

void loop() {
  while (bt.available()) {
    char c = bt.read();
    if (c == '\n' || c == '\r') {
      line.trim();
      if      (line == "on")  digitalWrite(LED, HIGH);
      else if (line == "off") digitalWrite(LED, LOW);
      else if (line == "status") bt.println(digitalRead(LED) ? "ON" : "OFF");
      line = "";
    } else {
      line += c;
    }
  }
}
