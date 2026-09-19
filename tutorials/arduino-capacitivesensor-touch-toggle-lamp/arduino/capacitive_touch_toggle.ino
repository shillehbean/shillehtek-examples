// Reads a capacitive sensor (coin electrode) and toggles an output pin (LED or relay) with auto-calibration, debounce, and baseline drift tracking; also prints readings to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-capacitivesensor-touch-toggle-lamp
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <CapacitiveSensor.h>

CapacitiveSensor cs(2, 4);            // send pin 2, receive (electrode) pin 4
const int OUT = 8;                    // LED now, relay IN later
long baseline = 0;
bool state = false, wasTouched = false;
unsigned long lastToggle = 0;

long readTouch() { return cs.capacitiveSensor(30); }   // 30 samples per reading

void setup() {
  Serial.begin(9600);
  pinMode(OUT, OUTPUT);
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF); // we'll do our own calibration
  delay(500);
  long sum = 0;
  for (int i = 0; i < 20; i++) { sum += readTouch(); delay(10); }
  baseline = sum / 20;                // idle reading with nobody near
  Serial.print("baseline "); Serial.println(baseline);
}

void loop() {
  long v = readTouch();
  bool touched = v > baseline * 4 + 200;             // well above idle
  Serial.println(v);

  if (touched && !wasTouched && millis() - lastToggle > 300) {   // rising edge + debounce
    state = !state;
    digitalWrite(OUT, state);
    lastToggle = millis();
  }
  wasTouched = touched;

  if (!touched) baseline = (baseline * 99 + v) / 100;  // slowly track drift while idle
  delay(10);
}
