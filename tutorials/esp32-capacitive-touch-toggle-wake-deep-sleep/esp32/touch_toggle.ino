// Read an ESP32 capacitive touch pad, debounce touches, toggle an LED (or relay input) and print ON/OFF to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-capacitive-touch-toggle-wake-deep-sleep
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int PAD = T0;            // GPIO 4
const int LED = 2;             // later: relay IN
int baseline = 0;              // idle reading measured at boot
bool state = false, wasTouched = false;
unsigned long lastToggle = 0;

int readPad() {                // average a few samples to kill jitter
  long sum = 0;
  for (int i = 0; i < 8; i++) sum += touchRead(PAD);
  return sum / 8;
}

bool touched() {
  int v = readPad();
  return v < baseline * 0.6;   // classic ESP32: value drops when touched
  // ESP32-S2/S3: use  v > baseline * 1.4  instead (value rises)
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  delay(300);
  baseline = readPad();        // don't touch the pad while booting
  Serial.printf("baseline %d\n", baseline);
}

void loop() {
  bool now = touched();
  if (now && !wasTouched && millis() - lastToggle > 250) {   // rising edge + debounce
    state = !state;
    digitalWrite(LED, state);
    lastToggle = millis();
    Serial.println(state ? "ON" : "OFF");
  }
  wasTouched = now;
  delay(20);
}
