// Reads a piezo sensor, flashes an LED on each knock, counts knocks within a timing window, and unlocks an active-low relay when the secret knock count is matched.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-piezo-knock-sensor-secret-relay-lock
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int PIEZO = A5, LED = 9, RELAY = 7;
const int THRESHOLD = 120;                 // raise it if footsteps trigger it
const int SECRET_KNOCKS = 3;               // knock this many times...
const unsigned long WINDOW   = 1500;       // ...within this many milliseconds
const unsigned long DEBOUNCE = 120;        // ignore the ringing after each hit

int knocks = 0;
unsigned long firstKnock = 0, lastKnock = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);               // active-LOW relay board: HIGH = locked
}

void loop() {
  int level = analogRead(PIEZO);

  if (level > THRESHOLD && millis() - lastKnock > DEBOUNCE) {
    lastKnock = millis();
    if (knocks == 0) firstKnock = lastKnock;
    knocks++;
    Serial.print("Knock "); Serial.print(knocks);
    Serial.print("  level "); Serial.println(level);
    digitalWrite(LED, HIGH); delay(30); digitalWrite(LED, LOW);   // flash per knock
  }

  // window closed: judge the pattern
  if (knocks > 0 && millis() - firstKnock > WINDOW) {
    if (knocks == SECRET_KNOCKS) {
      Serial.println("Secret knock! Unlocking for 3 s");
      digitalWrite(RELAY, LOW); digitalWrite(LED, HIGH);
      delay(3000);
      digitalWrite(RELAY, HIGH); digitalWrite(LED, LOW);
    } else {
      Serial.println("Wrong pattern");
      for (int i = 0; i < 3; i++) {        // angry triple blink
        digitalWrite(LED, HIGH); delay(80); digitalWrite(LED, LOW); delay(80);
      }
    }
    knocks = 0;
  }
}
