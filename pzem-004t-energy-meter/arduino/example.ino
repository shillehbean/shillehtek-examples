// Reads voltage, current, power, energy, frequency and power factor from a PZEM-004T using SoftwareSerial on an Arduino Uno and prints the values to the USB serial console every second.
//
// Buy this module: https://shillehtek.com/products/pzem-004t-ac-energy-meter-current-transformer
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pzem-004t-ac-energy-meter-current-transformer-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PZEM-004T V3 - Arduino Example
// TX->D10, RX->D11 (Uno, SoftwareSerial) | Library: "PZEM004Tv30"

#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

SoftwareSerial pzemSerial(10, 11);   // RX, TX
PZEM004Tv30 pzem(pzemSerial);

void setup() {
  Serial.begin(115200);
  Serial.println("PZEM-004T energy monitor");
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power   = pzem.power();
  float energy  = pzem.energy();
  float freq    = pzem.frequency();
  float pf      = pzem.pf();

  if (isnan(voltage)) {
    Serial.println("No response - check wiring and mains presence");
  } else {
    Serial.print(voltage);  Serial.print(" V | ");
    Serial.print(current);  Serial.print(" A | ");
    Serial.print(power);    Serial.print(" W | ");
    Serial.print(energy, 3);Serial.print(" kWh | ");
    Serial.print(freq);     Serial.print(" Hz | PF ");
    Serial.println(pf);
  }
  delay(1000);
}
