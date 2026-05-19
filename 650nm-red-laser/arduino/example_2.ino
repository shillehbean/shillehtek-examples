// Implements a laser tripwire: reads an LDR on A0 and activates a buzzer on pin 8 when the beam is interrupted (reading drops below a threshold).
//
// Buy this module: https://shillehtek.com/products/shillehtek-6mm-650nm-5mw-red-laser-diode-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-6mm-650nm-5mw-red-laser-diode-module-manual
// More examples: https://github.com/shillehtek/examples
//

// Laser tripwire: laser hits an LDR; if the beam is broken, the LDR
// reading drops and we trigger an alarm.
// Setup: laser pointed at LDR; LDR in voltage-divider with 10k pull-down on A0.

const int ldrPin = A0;
const int buzzPin = 8;
const int threshold = 600;   // calibrate to your setup

void setup() {
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  int v = analogRead(ldrPin);
  Serial.println(v);
  if (v < threshold) {
    digitalWrite(buzzPin, HIGH);   // alarm
  } else {
    digitalWrite(buzzPin, LOW);
  }
  delay(50);
}
