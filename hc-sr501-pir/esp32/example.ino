// ESP32 example using a hardware interrupt on GPIO4 to set a flag when motion is detected, printing detection events from the main loop after a warm-up period.
//
// Buy this module: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr501-pir-motion-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HC-SR501 PIR on ESP32 - interrupt-driven motion detection

const int pirPin = 4;
volatile bool motion = false;

void IRAM_ATTR onMotion() {
  motion = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pirPin), onMotion, RISING);
  Serial.println("PIR ready (warming up...).");
  delay(30000);
}

void loop() {
  if (motion) {
    motion = false;
    Serial.println("Motion detected!");
  }
  delay(50);
}
