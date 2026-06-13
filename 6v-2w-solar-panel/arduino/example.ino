// Reads the panel voltage via a 100k/100k voltage divider on A0 and prints the measured voltage and a simple sun/lighting status to Serial.
//
// Buy this module: https://shillehtek.com/products/110-x-136mm-6v-2w-solar-panel
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/110-x-136mm-6v-2w-solar-panel-manual
// More examples: https://github.com/shillehtek/examples
//

// 6V 2W Solar Panel Voltage Monitor - Arduino Uno / Nano
// Wire panel red through 100k/100k divider to A0.

const int PANEL_PIN = A0;
const float VREF = 5.0;          // Uno/Nano ADC reference
const float DIVIDER_RATIO = 2.0; // 100k + 100k -> halves the voltage

void setup() {
  Serial.begin(9600);
  Serial.println("Solar Panel Monitor");
}

void loop() {
  int raw = analogRead(PANEL_PIN);
  float vPin = (raw / 1023.0) * VREF;
  float vPanel = vPin * DIVIDER_RATIO;

  Serial.print("Panel: ");
  Serial.print(vPanel, 2);
  Serial.print(" V");

  if (vPanel > 5.5) {
    Serial.println("  [Full sun]");
  } else if (vPanel > 4.0) {
    Serial.println("  [Partial sun]");
  } else if (vPanel > 2.0) {
    Serial.println("  [Cloudy / shade]");
  } else {
    Serial.println("  [Dark]");
  }

  delay(2000);
}
