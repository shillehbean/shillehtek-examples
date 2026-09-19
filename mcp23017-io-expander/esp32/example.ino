// Initializes the MCP23017 on an ESP32 (SDA=21, SCL=22) and cycles a chasing LED effect across all 16 GPIO pins.
//
// Buy this module: https://shillehtek.com/products/mcp23017-i2c-16bit-io-port-expander-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mcp23017-i2c-16bit-io-port-expander-presoldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MCP23017 - ESP32 Example: chase across all 16 pins
// SDA->21, SCL->22 | Library: "Adafruit MCP23017"

#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if (!mcp.begin_I2C(0x20)) {
    Serial.println("MCP23017 not found");
    while (1) delay(10);
  }
  for (int p = 0; p < 16; p++) mcp.pinMode(p, OUTPUT);
}

void loop() {
  for (int p = 0; p < 16; p++) {       // GPA0..7 then GPB0..7
    mcp.digitalWrite(p, HIGH);
    delay(60);
    mcp.digitalWrite(p, LOW);
  }
}
