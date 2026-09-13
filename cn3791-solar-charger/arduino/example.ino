// Reads the battery voltage on an Arduino via a 100k/100k divider, prints the voltage over serial, and blinks the onboard LED rapidly when the battery is below a defined threshold.
//
// Buy this module: https://shillehtek.com/products/Battery
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cn3791-6v-mppt-solar-charger-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// CN3791 Battery Voltage Monitor - Arduino Uno / Nano
// Wire BAT terminal to A0 through a 100k/100k divider to GND.

const int BAT_PIN = A0;
const float VREF = 5.0;          // Uno/Nano ADC reference
const float DIVIDER_RATIO = 2.0; // 100k + 100k -> halves the voltage
const float LOW_BAT_THRESHOLD = 3.3; // volts

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int raw = analogRead(BAT_PIN);
  float vPin = (raw / 1023.0) * VREF;
  float vBat = vPin * DIVIDER_RATIO;

  Serial.print("Battery: ");
  Serial.print(vBat, 2);
  Serial.println(" V");

  if (vBat < LOW_BAT_THRESHOLD) {
    // Blink rapidly as low-battery warning
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}
