// Blink the onboard LED on pin 13 every 500 ms and print a startup message over the USB serial port, waiting for the host serial connection (Leonardo-specific).
//
// Buy this module: https://shillehtek.com/products/arduino-leonardo-r3-atmega32u4
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-leonardo-r3-atmega32u4-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Leonardo R3 - Blink the onboard LED (pin 13) and print to Serial

const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) { ; }        // wait for USB serial (Leonardo-specific)
  Serial.println("Leonardo R3 is alive!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
