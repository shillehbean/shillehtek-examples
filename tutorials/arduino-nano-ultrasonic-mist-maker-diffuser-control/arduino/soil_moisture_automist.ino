// Reads a capacitive soil moisture sensor and toggles a relay to run the mist maker on a timed cycle when the soil is dry.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ultrasonic-mist-maker-diffuser-control
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SOIL = A0;
const int MIST = 7;
const int DRY  = 750;     // calibrate
const int OK_  = 500;     // stop when above this

void setup() {
  pinMode(MIST, OUTPUT);
  digitalWrite(MIST, HIGH);     // active LOW relay = OFF
}
void loop() {
  int v = analogRead(SOIL);
  if (v < DRY) {
    digitalWrite(MIST, LOW);    // ON
    delay(30000);
    digitalWrite(MIST, HIGH);   // OFF
    delay(300000);              // wait 5 min for absorption
  } else {
    delay(60000);
  }
}
