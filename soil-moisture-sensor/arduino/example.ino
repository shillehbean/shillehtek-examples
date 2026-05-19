// Reads the analog value on A0, maps it to a calibrated moisture percentage, prints raw and percent values to the serial console, and reports a dry alarm from the digital output.
//
// Buy this module: https://shillehtek.com/products/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit-manual
// More examples: https://github.com/shillehtek/examples
//

// Soil Moisture Sensor - print analog reading and percent on Arduino
// Calibrate DRY_VAL by holding the probe in air, WET_VAL by submerging in water.

const int aoPin = A0;
const int doPin = 2;

const int DRY_VAL = 880;   // air / very dry
const int WET_VAL = 350;   // submerged in water

void setup() {
  Serial.begin(9600);
  pinMode(doPin, INPUT);
}

void loop() {
  int raw = analogRead(aoPin);
  int pct = map(raw, DRY_VAL, WET_VAL, 0, 100);
  pct = constrain(pct, 0, 100);

  Serial.print("Raw=");  Serial.print(raw);
  Serial.print("  Moisture="); Serial.print(pct); Serial.print(" %");
  if (digitalRead(doPin) == LOW) Serial.print("  [DRY ALARM]");
  Serial.println();

  delay(1000);
}
