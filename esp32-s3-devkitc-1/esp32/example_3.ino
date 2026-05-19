// Reads a capacitive touch value from touch-capable pin T1 (GPIO1) with touchRead, prints the measured value, and logs when the value exceeds a threshold.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-devkitc-1-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-devkitc-1-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

// The ESP32-S3 has 14 touch-capable pins: T1-T14 (GPIO1 - GPIO14).
// Touch a wire connected to the pin to see the value change.

#define TOUCH_PIN T1   // GPIO1

void setup() {
  Serial.begin(115200);
}

void loop() {
  uint32_t value = touchRead(TOUCH_PIN);
  Serial.print("Touch value: ");
  Serial.println(value);
  if (value > 30000) Serial.println("Touched!");
  delay(200);
}
