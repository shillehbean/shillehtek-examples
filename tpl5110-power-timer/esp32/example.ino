// Arduino-framework sketch for ESP32 that runs after each TPL5110 wake, performs a job, then pulses the DONE pin repeatedly so the TPL5110 will cut power.
//
// Buy this module: https://shillehtek.com/products/tpl5110-timer-module-pre-soldered-header
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tpl5110-timer-module-pre-soldered-header-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TPL5110 power timer - do one job, then tell the timer to cut the power
// The board is powered from the TPL5110 DRV pin, so this sketch restarts at every wake-up.
// Wiring: Done = D4 (Arduino) or GPIO 4 (ESP32), DRV = board power input, GND = GND
const int DONE_PIN = 4;

void setup() {
  pinMode(DONE_PIN, OUTPUT);
  digitalWrite(DONE_PIN, LOW);

  Serial.begin(115200);
  Serial.println("Awake - doing the job");
  // Put your own work here: read a sensor, then send or store the result.
  delay(500);
  Serial.println("Finished - asking the timer to cut power");
  Serial.flush();
}

void loop() {
  // Pulse Done until the power disappears
  digitalWrite(DONE_PIN, HIGH);
  delay(1);
  digitalWrite(DONE_PIN, LOW);
  delay(1);
}
