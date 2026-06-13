// Measures a 2S pack voltage on ESP32 ADC pin 34 using a 330k/100k divider (divider ratio 4.3), converts the ADC reading to pack voltage, and prints it over Serial once per second.
//
// Buy this module: https://shillehtek.com/products/18650
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx-2s-jh20-2s-7-4v-18650-lithium-battery-protection-board-10a-with-balancer-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 reads pack voltage through a 330k/100k divider
// 8.4V / 4.3 = 1.95V at ADC -- well within 3.3V range

const int adcPin = 34;
const float dividerRatio = (330.0 + 100.0) / 100.0;  // = 4.3
const float vRef = 3.3;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 4095.0) * vRef;
  float vPack = vAdc * dividerRatio;
  Serial.printf("Pack: %.2f V\n", vPack);
  delay(1000);
}
