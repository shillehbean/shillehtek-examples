// Reads the sensor on analog A0, maps a calibrated raw ADC range to a 0–100% moisture value, and prints raw and percent readings to the Serial console every second.
//
// Buy this module: https://shillehtek.com/products/Analog
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/capacitive-soil-moisture-sensor-v1-2-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Capacitive Soil Moisture Sensor V1.2 - Arduino
// AOUT -> A0, VCC -> 5V, GND -> GND

const int SOIL_PIN = A0;

// Calibrate these for your sensor + soil:
const int DRY_VALUE = 590;  // raw ADC reading in dry air
const int WET_VALUE = 250;  // raw ADC reading fully submerged

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(SOIL_PIN);

  // Constrain and map to 0-100% (higher = wetter)
  int clamped = constrain(raw, WET_VALUE, DRY_VALUE);
  int percent = map(clamped, DRY_VALUE, WET_VALUE, 0, 100);

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  Moisture: ");
  Serial.print(percent);
  Serial.println("%");

  delay(1000);
}
