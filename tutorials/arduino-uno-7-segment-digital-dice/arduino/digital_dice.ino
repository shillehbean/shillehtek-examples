// Arduino sketch that drives a 7-segment display and a push button to simulate rolling a six-sided die with an animated roll and proper random seeding.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-7-segment-digital-dice
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};   // a b c d e f g
const int BTN = 10;

//                         gfedcba
const byte digits[7] = { 0b0000000,   // (unused 0)
                         0b0000110,   // 1
                         0b1011011,   // 2
                         0b1001111,   // 3
                         0b1100110,   // 4
                         0b1101101,   // 5
                         0b1111101 }; // 6

void show(int n) {
  for (int s = 0; s < 7; s++)
    digitalWrite(segPins[s], bitRead(digits[n], s));
}

void setup() {
  for (int s = 0; s < 7; s++) pinMode(segPins[s], OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  randomSeed(analogRead(A0));    // floating pin noise = real randomness
  show(1);
}

void loop() {
  if (digitalRead(BTN) == LOW) {
    for (int i = 0; i < 12; i++) {      // roll animation
      show(random(1, 7));
      delay(60 + i * 15);                // slowing flicker, casino style
    }
    show(random(1, 7));                  // the actual roll
    delay(300);
  }
}
