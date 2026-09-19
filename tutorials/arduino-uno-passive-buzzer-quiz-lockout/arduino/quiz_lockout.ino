// Arduino sketch that implements a four-player quiz buzzer lockout: reads player buttons, locks out after the first press, lights the winner's LED, sounds a tone, and handles the host reset button.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-passive-buzzer-quiz-lockout
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int N = 4;
const int BTN[N] = {2, 3, 4, 5};
const int LED[N] = {8, 9, 10, 11};
const int TONE_HZ[N] = {523, 659, 784, 988};     // C, E, G, B: one note per player
const int HOST_BTN = 6, HOST_LED = 7, BUZZ = 12;

int winner = -1;                                  // -1 = nobody yet (armed)

void reset() {
  winner = -1;
  for (int i = 0; i < N; i++) digitalWrite(LED[i], LOW);
  digitalWrite(HOST_LED, HIGH);                   // ready light on
  tone(BUZZ, 300, 80);
  delay(300);                                     // ignore the reset button bounce
}

void setup() {
  for (int i = 0; i < N; i++) { pinMode(BTN[i], INPUT_PULLUP); pinMode(LED[i], OUTPUT); }
  pinMode(HOST_BTN, INPUT_PULLUP); pinMode(HOST_LED, OUTPUT); pinMode(BUZZ, OUTPUT);
  Serial.begin(9600);
  reset();
}

void loop() {
  if (winner < 0) {                               // armed: look for the first press
    for (int i = 0; i < N; i++) {
      if (digitalRead(BTN[i]) == LOW) {
        winner = i;                               // lockout: nobody else can win now
        digitalWrite(HOST_LED, LOW);
        digitalWrite(LED[i], HIGH);
        tone(BUZZ, TONE_HZ[i], 600);
        Serial.print("Player "); Serial.print(i + 1); Serial.println(" buzzed in!");
        break;
      }
    }
  } else {                                        // locked: blink the winner, wait for host
    digitalWrite(LED[winner], (millis() / 250) % 2);
  }

  if (digitalRead(HOST_BTN) == LOW) reset();
}
