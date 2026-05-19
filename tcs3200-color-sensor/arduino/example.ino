// Reads raw pulse widths for red, green, and blue channels from the TCS3200 on an Arduino (20% frequency scaling) and prints them over Serial.
//
// Buy this module: https://shillehtek.com/products/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects-manual
// More examples: https://github.com/shillehtek/examples
//

// GY-31 TCS3200 - Read raw red, green, blue frequencies on Arduino
// S0/S1 set frequency scaling. S2/S3 select which color filter is active.
// Lower frequency on a color = more of that color reflected.

const int S0  = 4;
const int S1  = 5;
const int S2  = 6;
const int S3  = 7;
const int OUT = 8;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  // Set frequency scaling to 20% (S0=H, S1=L)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

unsigned long readColor(int s2, int s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(50);
  return pulseIn(OUT, LOW);  // microseconds per low half-cycle
}

void loop() {
  unsigned long red   = readColor(LOW,  LOW);
  unsigned long blue  = readColor(LOW,  HIGH);
  unsigned long green = readColor(HIGH, HIGH);

  Serial.print("R="); Serial.print(red);
  Serial.print("  G="); Serial.print(green);
  Serial.print("  B="); Serial.println(blue);

  delay(300);
}
