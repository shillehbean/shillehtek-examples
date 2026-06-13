// Reads Celsius and Fahrenheit from a MAX6675 on an Arduino using the Adafruit MAX6675 library and prints values to Serial, with a check for a disconnected thermocouple.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max6675-module-k-type-thermocouple-sensor-measures-up-to-1024-degrees-manual
// More examples: https://github.com/shillehtek/examples
//

// MAX6675 K-type thermocouple - Arduino
// Library: Adafruit MAX6675 (Library Manager)

#include <max6675.h>

const int CS_PIN  = 5;
const int SCK_PIN = 6;
const int SO_PIN  = 4;

MAX6675 thermo(SCK_PIN, CS_PIN, SO_PIN);

void setup() {
  Serial.begin(9600);
  delay(500); // chip needs time to stabilize on first power-up
  Serial.println("MAX6675 ready");
}

void loop() {
  float c = thermo.readCelsius();
  float f = thermo.readFahrenheit();

  if (isnan(c)) {
    Serial.println("Thermocouple disconnected!");
  } else {
    Serial.print("Temp: ");
    Serial.print(c);
    Serial.print(" C  /  ");
    Serial.print(f);
    Serial.println(" F");
  }

  delay(250); // MAX6675 needs ~220ms between reads
}
