// Publishes the joystick axes and buttons as a USB HID gamepad using the Joystick library (for ATmega32U4-based boards like Pro Micro).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-joystick-shield-usb-gamepad-nrf24-transmitter
// Parts used: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
//             https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Joystick.h>

Joystick_ Joy;

void setup() {
  Joy.begin();
  for (int p : BTN_PINS) pinMode(p, INPUT_PULLUP);
}

void loop() {
  Joy.setXAxis(map(analogRead(A0), 0, 1023, -127, 127));
  Joy.setYAxis(map(analogRead(A1), 0, 1023, -127, 127));

  for (int i = 0; i < 7; i++) {
    Joy.setButton(i, digitalRead(BTN_PINS[i]) == LOW);
  }

  delay(10);
}
