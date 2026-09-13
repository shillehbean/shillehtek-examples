// Reads battery voltage on an ESP32 ADC pin (GPIO34) through a 220k/100k divider, converts the 12-bit ADC value to the actual battery voltage, and prints it over Serial once per second.
//
// Buy this module: https://shillehtek.com/products/18650
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1s-3-7v-3a-2mos-bms-li-ion-18650-battery-protection-board-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32 reads P+ through a 220k/100k divider (max 3.3V at ADC)
// Connect: P+ -- 220k -- ADC34 -- 100k -- GND

const int adcPin = 34;
const float dividerRatio = (220.0 + 100.0) / 100.0;  // = 3.2
const float vRef = 3.3;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 4095.0) * vRef;
  float vBat = vAdc * dividerRatio;
  Serial.printf("Battery: %.2f V\n", vBat);
  delay(1000);
}
