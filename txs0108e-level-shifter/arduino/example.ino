// Toggle a digital output on an Arduino (A1) to produce a 1 Hz 5V-level signal on the TXS0108E B1 channel while printing state to Serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter-manual
// More examples: https://github.com/shillehtek/examples
//

// TXS0108E Logic Level Converter - Arduino Test
// Toggles a 5V output line driven from Arduino through channel B1.
// Wire: Arduino D8 -> A1, B1 -> 5V LED through 220 ohm resistor to GND
// VA = 3.3V, VB = 5V, OE = 3.3V

const int signalPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(signalPin, OUTPUT);
  Serial.println("TXS0108E ready - toggling B1 at 1 Hz");
}

void loop() {
  digitalWrite(signalPin, HIGH);  // Drive A1 HIGH -> B1 outputs ~5V
  Serial.println("HIGH");
  delay(500);

  digitalWrite(signalPin, LOW);   // Drive A1 LOW -> B1 outputs 0V
  Serial.println("LOW");
  delay(500);
}
