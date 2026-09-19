// Reads voltage, current and power from a PZEM-004T module using the PZEM004Tv40_R4 library and prints the values over the serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-pzem-004t-fast-ac-power-kwh-readings
// Parts used: https://shillehtek.com/products/pzem-004t-ac-energy-meter-current-transformer
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <PZEM004Tv40_R4.h>

// Create PZEM object on hardware Serial1 (UNO R4)
// For UNO R3 / Nano, construct with SoftwareSerial pins instead
PZEM004Tv40_R4 pzem(&Serial1);

void setup() {
  Serial.begin(115200);
  pzem.begin();
}

void loop() {
  // Read all values in one ~200 ms transaction
  if (pzem.readAll()) {
    Serial.print("Voltage: ");
    Serial.print(pzem.getVoltage(), 1);
    Serial.println(" V");

    Serial.print("Current: ");
    Serial.print(pzem.getCurrent(), 3);
    Serial.println(" A");

    Serial.print("Power: ");
    Serial.print(pzem.getPower(), 1);
    Serial.println(" W");
  }

  delay(1000);
}
