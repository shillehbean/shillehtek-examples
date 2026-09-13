// Simple Arduino sketch for the Blue Pill that sends "Hello, Blue Pill!" over the serial port once per second.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32-blue-pill-usb-ttl-upload-first-sketch
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
//             https://shillehtek.com/products/shillehtek-unsoldered-stm32f103c8t6-blue-pill-arm-development-board-kit-pro-usb-v
//             https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  // Start the Serial communication at 9600 baud
  Serial.begin(9600);

  // Wait for the serial port to connect (necessary for some boards)
  while (!Serial) {
    ; // Wait
  }
}

void loop() {
  // Print a message to the Serial Monitor
  Serial.println("Hello, Blue Pill!");

  // Wait for 1 second
  delay(1000);
}
