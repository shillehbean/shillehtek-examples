// Uses an ESP32 to measure 4S pack voltage on ADC34 and toggles a relay on GPIO25 when the pack voltage falls below a configurable cutoff, while printing status to Serial.
//
// Buy this module: https://shillehtek.com/products/14.8V
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4s-30a-18650-lithium-battery-protection-board-14-8v-16v-with-cable-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ESP32 reads 4S pack voltage via 680k/100k divider on GPIO34
// Trigger a "low battery" relay on GPIO25 when pack drops below 12.5V

const int adcPin = 34;
const int relayPin = 25;
const float dividerRatio = 7.8;
const float vRef = 3.3;
const float cutoffV = 12.5;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(adcPin);
  float vAdc = (raw / 4095.0) * vRef;
  float vPack = vAdc * dividerRatio;

  if (vPack < cutoffV) {
    digitalWrite(relayPin, HIGH);  // Shut down load
    Serial.printf("LOW BATTERY %.2f V -- relay opened\n", vPack);
  } else {
    digitalWrite(relayPin, LOW);
    Serial.printf("Pack: %.2f V\n", vPack);
  }
  delay(2000);
}
