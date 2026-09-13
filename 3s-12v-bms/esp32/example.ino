// Uses an ESP32 ADC pin (GPIO34) to read the divided pack voltage, scales it back to the pack voltage using the divider ratio, and prints the pack voltage over serial.
//
// Buy this module: https://shillehtek.com/products/12V
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3s-12v-18650-lithium-battery-protection-board-11-1v-12-6v-balanced-25a-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32 reads 3S pack voltage through a 470k/100k divider on GPIO34
// 12.6V / 5.7 = 2.21V at ADC -- safely below 3.3V

const int adcPin = 34;
const float dividerRatio = (470.0 + 100.0) / 100.0;  // = 5.7
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
