// Reads the TCRT5000 analog (AO) and digital (DO) outputs and prints the raw ADC value plus a digital line-detected status to the Serial console every 100 ms.
//
// Buy this module: https://shillehtek.com/products/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot-manual
// More examples: https://github.com/shillehtek/examples
//

// TCRT5000 - Print analog and digital readings on Arduino
// Wire VCC=5V, GND=GND, AO=A0, DO=D2 (optional)

const int aoPin = A0;
const int doPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(doPin, INPUT);
}

void loop() {
  int raw = analogRead(aoPin);
  int line = digitalRead(doPin);

  Serial.print("Raw=");  Serial.print(raw);
  Serial.print("   DO="); Serial.print(line);
  Serial.println(line == LOW ? "  [LINE DETECTED]" : "");

  delay(100);
}
