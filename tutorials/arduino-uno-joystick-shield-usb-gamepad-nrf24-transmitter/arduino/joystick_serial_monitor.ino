// Reads X/Y analog axes and seven digital buttons from the joystick shield and prints their values to the serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-joystick-shield-usb-gamepad-nrf24-transmitter
// Parts used: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
//             https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int BTN_PINS[] = {2, 3, 4, 5, 6, 7, 8};
const char* BTN_NAMES[] = {"A", "E", "C", "D", "F", "B", "Z"};

void setup() {
  Serial.begin(9600);
  for (int p : BTN_PINS) pinMode(p, INPUT_PULLUP);
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);

  Serial.print("X:"); Serial.print(x);
  Serial.print(" Y:"); Serial.print(y);
  Serial.print(" Btns:");

  for (int i = 0; i < 7; i++) {
    if (digitalRead(BTN_PINS[i]) == LOW) {
      Serial.print(BTN_NAMES[i]);
      Serial.print(" ");
    }
  }

  Serial.println();
  delay(100);
}
