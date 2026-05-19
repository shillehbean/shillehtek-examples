// Reads RGB pulse widths on an ESP32, normalizes them using user-supplied calibration ranges to 0–255, and heuristically assigns a color name.
//
// Buy this module: https://shillehtek.com/products/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 + TCS3200: read R/G/B and guess a color name
// Calibrate MIN/MAX values by holding white and black under the sensor and
// noting the printed values, then update the constants below.

const int S0 = 18, S1 = 19, S2 = 21, S3 = 22, OUT = 23;

// Calibration -- replace with your own readings
const int R_MIN = 30, R_MAX = 250;
const int G_MIN = 35, G_MAX = 270;
const int B_MIN = 30, B_MAX = 240;

void setup() {
  Serial.begin(115200);
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH); digitalWrite(S1, LOW);  // 20% scaling
}

int read(int s2, int s3) {
  digitalWrite(S2, s2); digitalWrite(S3, s3);
  delay(50);
  return pulseIn(OUT, LOW);
}

int normalize(int v, int lo, int hi) {
  int n = map(v, lo, hi, 255, 0);
  return constrain(n, 0, 255);
}

void loop() {
  int r = normalize(read(LOW,  LOW),  R_MIN, R_MAX);
  int g = normalize(read(HIGH, HIGH), G_MIN, G_MAX);
  int b = normalize(read(LOW,  HIGH), B_MIN, B_MAX);

  String name = "?";
  if (r > 180 && g < 100 && b < 100) name = "RED";
  else if (g > 150 && r < 120 && b < 120) name = "GREEN";
  else if (b > 150 && r < 120 && g < 150) name = "BLUE";
  else if (r > 200 && g > 200 && b > 200) name = "WHITE";
  else if (r < 60 && g < 60 && b < 60)    name = "BLACK";

  Serial.printf("R=%3d  G=%3d  B=%3d  -> %s\n", r, g, b, name.c_str());
  delay(400);
}
