// Uses an interrupt on an ESP32 to timestamp motion events from the RCWL-0516, prints event times to Serial, and mirrors the sensor state to an LED.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rcwl-0516-microwave-doppler-radar-motion-sensor-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// RCWL-0516 motion sensor on ESP32
// OUT pin -> GPIO13

const uint8_t SENSOR_PIN = 13;
const uint8_t LED_PIN    = 2;

volatile bool motionFlag = false;
unsigned long lastEventMs = 0;

void IRAM_ATTR onMotion() {
  motionFlag = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(SENSOR_PIN, onMotion, RISING);
  Serial.println("RCWL-0516 on ESP32 ready");
}

void loop() {
  if (motionFlag) {
    motionFlag = false;
    lastEventMs = millis();
    Serial.printf("[%lu ms] Motion detected\n", lastEventMs);
  }

  digitalWrite(LED_PIN, digitalRead(SENSOR_PIN));
  delay(20);
}
