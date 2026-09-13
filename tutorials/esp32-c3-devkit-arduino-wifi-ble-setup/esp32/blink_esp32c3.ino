// Blink the on-board LED and print a greeting on the serial console to verify the ESP32-C3 board and basic I/O/serial functionality.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c3-devkit-arduino-wifi-ble-setup
// Parts used: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LED = 8;   // built-in LED on most C3 boards

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}
void loop() {
  Serial.println("hello from ESP32-C3");
  digitalWrite(LED, HIGH); delay(500);
  digitalWrite(LED, LOW);  delay(500);
}
