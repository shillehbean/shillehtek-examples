// Reads raw red, green, and blue pulse durations from a TCS3200 sensor and prints the values to the Serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-tcs3200-read-rgb-values
// Parts used: https://shillehtek.com/products/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int S0 = 4, S1 = 5, S2 = 6, S3 = 7, OUT = 8;

void setup() {
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH); digitalWrite(S1, HIGH);  // 100% scaling
  Serial.begin(9600);
}

int readChannel(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(50);
  return pulseIn(OUT, LOW);
}

void loop() {
  int red   = readChannel(LOW,  LOW);
  int blue  = readChannel(LOW,  HIGH);
  int green = readChannel(HIGH, HIGH);
  Serial.print("R="); Serial.print(red);
  Serial.print(" G="); Serial.print(green);
  Serial.print(" B="); Serial.println(blue);
  delay(200);
}
