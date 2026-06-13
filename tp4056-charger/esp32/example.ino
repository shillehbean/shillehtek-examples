// Uses an ESP32 ADC (GPIO34) to measure the battery via a high-value divider and reads the TP4056 CHRG and STDBY open-drain signal pins (with pull-ups) to report voltage, charging, and full states.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tp4056-1a-lipo-battery-charging-board-type-c-with-current-protection-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 TP4056 monitor
// Cell voltage: OUT+ -- 220k -- GPIO34 -- 100k -- GND
// CHRG LED tap: GPIO32 (HIGH when charging)
// STDBY LED tap: GPIO33 (HIGH when full)
// Note: the LED pins on TP4056 are open-drain -- pull them up to 3.3V via 10k

const int adcPin = 34;
const int chrgPin = 32;
const int stdbyPin = 33;
const float dividerRatio = 3.2;
const float vRef = 3.3;

void setup() {
  Serial.begin(115200);
  pinMode(chrgPin, INPUT_PULLUP);
  pinMode(stdbyPin, INPUT_PULLUP);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(adcPin);
  float vBat = (raw / 4095.0) * vRef * dividerRatio;

  bool charging = (digitalRead(chrgPin) == LOW);   // LED on = pin pulled low
  bool full     = (digitalRead(stdbyPin) == LOW);

  Serial.printf("Cell: %.2f V | Charging: %d | Full: %d\n", vBat, charging, full);
  delay(1500);
}
