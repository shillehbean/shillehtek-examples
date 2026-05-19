// Generates a 1 kHz square-wave test tone on Arduino digital pin D9 (through a 1 µF coupling capacitor to Audio IN+) to perform a simple mono audio test of the TPA3118.
//
// Buy this module: https://shillehtek.com/products/tpa3118-pbtl-single-digital-amplifier-board-1x60w
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tpa3118-pbtl-single-digital-amplifier-board-1x60w-manual
// More examples: https://github.com/shillehtek/examples
//

// Arduino - drive TPA3118 with a square wave tone
// Connect D9 -- 1uF cap -- Audio IN+
// Audio IN- to Arduino GND

void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  tone(9, 1000);  // 1 kHz tone
  delay(500);
  noTone(9);
  delay(500);
}
