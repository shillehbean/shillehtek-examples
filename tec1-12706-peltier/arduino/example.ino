// Implements simple bang-bang (on/off) temperature control with hysteresis using a MOSFET-driven Peltier and a placeholder temperature read function.
//
// Buy this module: https://shillehtek.com/products/peltier-module-tec1-12706-12v-40x40mm
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/peltier-module-tec1-12706-12v-40x40mm-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TEC1-12706 bang-bang control with hysteresis.
// Wiring: MOSFET gate -> D9 (through ~220R), Peltier red -> +12V,
// Peltier black -> MOSFET drain, MOSFET source -> GND (shared with Arduino).
// Replace readTempC() with your sensor (DS18B20, thermistor, etc.).

const int MOSFET_PIN = 9;
const float TARGET_C   = 10.0;   // desired cold-plate temperature
const float HYSTERESIS = 2.0;    // degrees of swing allowed

float readTempC() {
  // TODO: replace with a real sensor read
  return analogRead(A0) * 0.1;   // placeholder
}

void setup() {
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  float t = readTempC();

  if (t > TARGET_C + HYSTERESIS) {
    digitalWrite(MOSFET_PIN, HIGH);   // cool
  } else if (t < TARGET_C - HYSTERESIS) {
    digitalWrite(MOSFET_PIN, LOW);    // rest
  }

  Serial.print("Temp: ");
  Serial.println(t);
  delay(1000);   // slow loop = gentle cycling
}
