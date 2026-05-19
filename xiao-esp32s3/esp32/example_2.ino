// Reads the capacitive touch pad on D2 (TOUCH3), prints the raw touch value to serial, and lights the D0 LED when a touch is detected (value < 20000).
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-S3 - Capacitive touch sensor on D2 (TOUCH3)
// Reading drops when the pad is touched.

#define TOUCH_PIN D2   // GPIO3 (TOUCH3)
#define LED_PIN   D0   // GPIO1

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int v = touchRead(TOUCH_PIN);
  Serial.println(v);
  digitalWrite(LED_PIN, v < 20000 ? HIGH : LOW);
  delay(50);
}
