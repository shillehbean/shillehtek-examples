// Reads the analog TDS probe on an Arduino A1, averages the ADC readings, applies temperature compensation, converts the voltage to TDS ppm, and prints the result over Serial.
//
// Buy this module: https://shillehtek.com/products/tds-water-sensor-module-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tds-water-sensor-module-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Analog TDS Meter - Arduino Example
// A->A1, +->5V, -->GND

const int tdsPin = A1;
const float VREF = 5.0;
float waterTemp = 25.0;      // replace with DS18B20 reading if available

float readVolts() {
  long total = 0;
  for (int i = 0; i < 30; i++) { total += analogRead(tdsPin); delay(3); }
  return total / 30.0 * VREF / 1023.0;
}

void setup() {
  Serial.begin(115200);
  Serial.println("TDS meter ready - dip the probe");
}

void loop() {
  float volts = readVolts();
  float compensation = 1.0 + 0.02 * (waterTemp - 25.0);
  float v = volts / compensation;

  float tds = (133.42 * v * v * v
             - 255.86 * v * v
             + 857.39 * v) * 0.5;

  Serial.print("V: ");
  Serial.print(volts, 3);
  Serial.print(" | TDS: ");
  Serial.print(tds, 0);
  Serial.println(" ppm");
  delay(1000);
}
