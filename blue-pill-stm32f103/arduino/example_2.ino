// Read a 0–3.3 V analog input on PA0 using the STM32's 12-bit ADC and print the raw value and calculated voltage over Serial1.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Read a potentiometer (or any 0-3.3V signal) on PA0.
// The STM32 ADC is 12-bit (0-4095), unlike Arduino's 10-bit.

const int POT_PIN = PA0;

void setup() {
  analogReadResolution(12);  // Use the full 12 bits
  pinMode(POT_PIN, INPUT_ANALOG);
  Serial1.begin(9600);
}

void loop() {
  int raw = analogRead(POT_PIN);
  float volts = raw * (3.3f / 4095.0f);

  Serial1.print("Raw: "); Serial1.print(raw);
  Serial1.print(" | V: "); Serial1.println(volts, 3);
  delay(200);
}
