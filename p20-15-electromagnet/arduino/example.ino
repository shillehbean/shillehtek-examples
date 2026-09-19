// Switch the P20/15 electromagnet on and off from an Arduino digital pin (D5) using a MOSFET, holding for 5 seconds then releasing for 3 seconds while printing status to Serial.
//
// Buy this module: https://shillehtek.com/products/electromagnet-solenoid-12v-3kg-p20-15
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/electromagnet-solenoid-12v-3kg-p20-15-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// P20/15 electromagnet via logic-level MOSFET on D5
// 12V supply for the magnet, grounds shared with the Arduino.
// Flyback diode across the magnet leads is mandatory.

const int MAGNET_PIN = 5;

void setup() {
  pinMode(MAGNET_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Magnet ON - holding");
  digitalWrite(MAGNET_PIN, HIGH);
  delay(5000);                      // hold for 5 s

  Serial.println("Magnet OFF - released");
  digitalWrite(MAGNET_PIN, LOW);
  delay(3000);                      // released for 3 s
}
