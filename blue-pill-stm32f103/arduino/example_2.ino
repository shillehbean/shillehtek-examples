// Read a 10k potentiometer on PA0 with a 12-bit ADC and print raw value and computed voltage over Serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32 Blue Pill - read a 10k potentiometer on PA0 (ADC channel 0)
// Wire pot ends to 3V3 and GND, wiper to PA0

const int potPin = PA0;

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT_ANALOG);
  analogReadResolution(12);   // 0 - 4095
}

void loop() {
  int raw = analogRead(potPin);
  float voltage = raw * 3.3 / 4095.0;
  Serial.print("Raw=");  Serial.print(raw);
  Serial.print("  V="); Serial.println(voltage, 3);
  delay(200);
}
