// Reads the MQ-2 analog output and digital alarm pin, prints the raw analog value over Serial, and sounds a buzzer when the analog reading exceeds a threshold or the digital output signals alarm.
//
// Buy this module: https://shillehtek.com/products/mq-2-flammable-gas-smoke-sensor-module-for-arduino-safety
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-2-flammable-gas-smoke-sensor-module-for-arduino-safety-manual
// More examples: https://github.com/shillehtek/examples
//

// MQ-2 - Print analog reading and trigger a buzzer if smoke/gas detected

const int aoPin   = A0;
const int doPin   = 2;
const int buzzer  = 8;

const int ALARM_THRESHOLD = 400;  // tune to your environment

void setup() {
  Serial.begin(9600);
  pinMode(doPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("MQ-2 warming up - wait 1-3 minutes for stable values");
}

void loop() {
  int raw = analogRead(aoPin);
  bool digitalAlarm = (digitalRead(doPin) == LOW);

  Serial.print("Raw="); Serial.print(raw);
  if (raw > ALARM_THRESHOLD || digitalAlarm) {
    Serial.print("  [ALARM]");
    tone(buzzer, 1000, 200);
  }
  Serial.println();
  delay(500);
}
