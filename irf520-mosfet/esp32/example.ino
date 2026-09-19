// Sets discrete PWM duty steps (off, low, mid, full) on GPIO 25 and prints the selected duty value over serial on an ESP32 board.
//
// Buy this module: https://shillehtek.com/products/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SIG = 25;

void setup() {
  Serial.begin(115200);
  pinMode(SIG, OUTPUT);
}

void loop() {
  int steps[] = {0, 96, 160, 255};   // off, low, mid, full
  for (int i = 0; i < 4; i++) {
    analogWrite(SIG, steps[i]);
    Serial.printf("Duty: %d/255\n", steps[i]);
    delay(3000);
  }
}
