// Uses the ESP32 hardware UART2 to query the PZEM-004T and print voltage, current, power, energy, frequency and power factor once per second (with an optional energy counter reset).
//
// Buy this module: https://shillehtek.com/products/pzem-004t-ac-energy-meter-current-transformer
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pzem-004t-ac-energy-meter-current-transformer-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PZEM-004T V3 - ESP32 Example (hardware UART2)
// TX->GPIO16, RX->GPIO17 | Library: "PZEM004Tv30"

#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(Serial2, 16, 17);   // UART2, RX=16, TX=17

void setup() {
  Serial.begin(115200);
}

void loop() {
  float v = pzem.voltage();
  if (isnan(v)) {
    Serial.println("No response from PZEM");
  } else {
    Serial.printf("%.1f V  %.3f A  %.1f W  %.3f kWh  %.1f Hz  PF %.2f\n",
                  v, pzem.current(), pzem.power(),
                  pzem.energy(), pzem.frequency(), pzem.pf());
  }
  delay(1000);

  // pzem.resetEnergy();   // uncomment once to zero the kWh counter
}
