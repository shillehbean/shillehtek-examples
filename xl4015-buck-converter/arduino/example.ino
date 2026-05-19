// Reads the XL4015 output via a 30k/10k voltage divider on A0, converts the ADC reading to actual rail voltage, and prints the value to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/dc-dc-xl4015-adjustable-step-down-module-5a-75w-with-3-bit-digital-voltmeter-display
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dc-dc-xl4015-adjustable-step-down-module-5a-75w-with-3-bit-digital-voltmeter-display-manual
// More examples: https://github.com/shillehtek/examples
//

// Monitor XL4015 output rail with Arduino ADC
// Voltage divider: OUT+ -- 30k -- A0 -- 10k -- GND
// Divides up to 22V down to ~5.5V at A0 (Arduino 5V tolerant)

const int sensePin = A0;
const float DIV_RATIO = (30000.0 + 10000.0) / 10000.0;

void setup() { Serial.begin(9600); }

void loop() {
  int raw = analogRead(sensePin);
  float vAtPin = raw * (5.0 / 1023.0);
  float vRail = vAtPin * DIV_RATIO;
  Serial.print("Rail: "); Serial.print(vRail, 2); Serial.println(" V");
  delay(500);
}
