// Reads RCWL-0516 OUT on an Arduino Uno using an external interrupt; prints "Motion detected!" to Serial and mirrors the sensor state to the onboard LED.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rcwl-0516-microwave-doppler-radar-motion-sensor-module-manual
// More examples: https://github.com/shillehtek/examples
//

// RCWL-0516 motion sensor on Arduino Uno
// OUT pin -> D2 (INT0)

const uint8_t SENSOR_PIN = 2;
const uint8_t LED_PIN    = 13;

volatile bool motionFlag = false;

void onMotion() {
  motionFlag = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), onMotion, RISING);
  Serial.println("RCWL-0516 ready");
}

void loop() {
  if (motionFlag) {
    motionFlag = false;
    Serial.println("Motion detected!");
  }

  // Mirror current state to onboard LED
  digitalWrite(LED_PIN, digitalRead(SENSOR_PIN));
  delay(50);
}
