// Initializes an Adafruit MCP23017 I2C expander and runs a simple LED chase on pins 8–15 (GPB0–GPB7).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-mcp23017-add-16-i2c-gpio-pins
// Parts used: https://shillehtek.com/products/mcp23017-i2c-16bit-io-port-expander-presoldered
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 expander;

void setup() {
  expander.begin(0);               // address offset 0 -> I2C 0x20
  for (int i = 8; i < 16; i++) {   // GPB0–GPB7 as outputs
    expander.pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 8; i < 16; i++) {   // chase the output LEDs
    expander.digitalWrite(i, HIGH);
    delay(150);
    expander.digitalWrite(i, LOW);
  }
}
