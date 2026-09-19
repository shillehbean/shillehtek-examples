// Initializes the MCP23017 at I2C address 0x20, sets GPA0 as an output to blink an LED, and configures GPB0 with an internal pull-up to detect a button press and print a message.
//
// Buy this module: https://shillehtek.com/products/mcp23017-i2c-16bit-io-port-expander-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mcp23017-i2c-16bit-io-port-expander-presoldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MCP23017 - Arduino Example
// SDA->A4, SCL->A5, addr 0x20 | Library: "Adafruit MCP23017"

#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(115200);
  if (!mcp.begin_I2C(0x20)) {
    Serial.println("MCP23017 not found - check wiring/address");
    while (1);
  }
  mcp.pinMode(0, OUTPUT);          // GPA0 = LED
  mcp.pinMode(8, INPUT_PULLUP);    // GPB0 = button (pins 8-15 = port B)
  Serial.println("16 extra GPIO online at 0x20");
}

void loop() {
  mcp.digitalWrite(0, HIGH);
  delay(250);
  mcp.digitalWrite(0, LOW);
  delay(250);

  if (mcp.digitalRead(8) == LOW) {
    Serial.println("Button on GPB0 pressed!");
  }
}
