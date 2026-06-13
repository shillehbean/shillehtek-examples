// Reads Celsius from a MAX6675 connected to an ESP32 using the Adafruit MAX6675 library and prints the temperature over Serial, handling a disconnected thermocouple.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max6675-module-k-type-thermocouple-sensor-measures-up-to-1024-degrees-manual
// More examples: https://github.com/shillehtek/examples
//

// MAX6675 K-type thermocouple - ESP32
// Same Adafruit MAX6675 library works fine on ESP32.

#include <max6675.h>

const int CS_PIN  = 5;   // GPIO5
const int SCK_PIN = 18;  // GPIO18
const int SO_PIN  = 19;  // GPIO19

MAX6675 thermo(SCK_PIN, CS_PIN, SO_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("MAX6675 ready");
}

void loop() {
  float c = thermo.readCelsius();
  if (isnan(c)) {
    Serial.println("Thermocouple disconnected!");
  } else {
    Serial.printf("Temp: %.2f C\n", c);
  }
  delay(300);
}
