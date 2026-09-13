// Provides a helper function that normalizes an analog axis reading to a -100..100 range with a configurable deadzone and mapping based on min/center/max values.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-joystick-shield-usb-gamepad-nrf24-transmitter
// Parts used: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
//             https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

int X_MIN = 0, X_CTR = 512, X_MAX = 1023, X_DEAD = 20;

int axisRead(int pin, int min, int ctr, int max, int dead) {
  int v = analogRead(pin) - ctr;
  if (abs(v) < dead) return 0;
  if (v > 0) return map(v, dead, max - ctr, 0, 100);
  return map(v, ctr - min, -dead, -100, 0);
}
