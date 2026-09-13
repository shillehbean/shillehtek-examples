// ESP32 Arduino sketch that reads a capacitive soil moisture sensor, converts the ADC value to a percentage, and activates a relay to run a pump when moisture is below a set threshold.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-capacitive-soil-moisture-smart-auto-watering
// Parts used: https://shillehtek.com/products/capacitive-soil-moisture-sensor-v1-2
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SENSOR = 34;
const int PUMP_RELAY = 26;
const int DRY_MAX = 2800;   // calibrate
const int WET_MIN = 1300;
const int THRESHOLD = 30;   // % moisture

void setup() {
  pinMode(PUMP_RELAY, OUTPUT);
  digitalWrite(PUMP_RELAY, HIGH);  // active LOW
  Serial.begin(115200);
}

void loop() {
  int raw = analogRead(SENSOR);
  int pct = constrain(map(raw, WET_MIN, DRY_MAX, 100, 0), 0, 100);
  Serial.printf("raw=%d pct=%d%%\n", raw, pct);
  if (pct < THRESHOLD) {
    digitalWrite(PUMP_RELAY, LOW);  delay(5000);
    digitalWrite(PUMP_RELAY, HIGH); delay(300000);
  } else {
    delay(60000);
  }
}
