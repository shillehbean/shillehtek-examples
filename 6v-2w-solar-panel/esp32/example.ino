// Performs oversampled ADC reads on GPIO34 to log the solar panel voltage on an ESP32 and prints a simple generation/status message over Serial.
//
// Buy this module: https://shillehtek.com/products/110-x-136mm-6v-2w-solar-panel
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/110-x-136mm-6v-2w-solar-panel-manual
// More examples: https://github.com/shillehtek/examples
//

// 6V 2W Panel + ESP32 - logs panel voltage to Serial.
// Wire panel red through 100k/100k divider to GPIO34.

const int PANEL_PIN = 34;
const float VREF = 3.3;
const float DIVIDER_RATIO = 2.0;

float readPanelVoltage() {
  uint32_t sum = 0;
  for (int i = 0; i < 32; i++) {
    sum += analogRead(PANEL_PIN);
    delay(2);
  }
  float raw = sum / 32.0;
  float vPin = (raw / 4095.0) * VREF;
  return vPin * DIVIDER_RATIO;
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("Solar Logger ready");
}

void loop() {
  float v = readPanelVoltage();
  Serial.printf("Panel: %.2f V\n", v);

  // Estimate generation status
  if (v > 5.0) {
    Serial.println("  Generating strongly");
  } else if (v > 3.0) {
    Serial.println("  Generating - partial light");
  } else {
    Serial.println("  Low / no generation");
  }

  delay(5000);
}
