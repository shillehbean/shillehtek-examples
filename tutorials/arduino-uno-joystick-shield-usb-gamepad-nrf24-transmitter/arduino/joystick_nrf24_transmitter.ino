// Reads the joystick axes and buttons and transmits the packed state over an nRF24L01+ radio as a simple wireless gamepad packet.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-joystick-shield-usb-gamepad-nrf24-transmitter
// Parts used: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
//             https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <RF24.h>

RF24 r(9, 10);   // CE, CSN per shield

struct __attribute__((packed)) Packet {
  int8_t x, y;
  uint8_t btns;
};

void setup() {
  r.begin();
  r.openWritingPipe(0xF0F0F0F0E1LL);
  r.setPALevel(RF24_PA_HIGH);

  for (int p : BTN_PINS) pinMode(p, INPUT_PULLUP);
}

void loop() {
  Packet p;
  p.x = map(analogRead(A0), 0, 1023, -127, 127);
  p.y = map(analogRead(A1), 0, 1023, -127, 127);

  p.btns = 0;
  for (int i = 0; i < 7; i++) {
    if (digitalRead(BTN_PINS[i]) == LOW) p.btns |= 1 << i;
  }

  r.write(&p, sizeof(p));
  delay(20);
}
