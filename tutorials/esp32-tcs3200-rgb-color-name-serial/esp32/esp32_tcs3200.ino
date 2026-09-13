// Defines ESP32 pin connections, a calibration struct, and functions to set TCS3200 scaling, read raw red/green/blue pulse widths, clamp/normalize readings between black and white calibration, and begins a color detection routine.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-tcs3200-rgb-color-name-serial
// Parts used: https://shillehtek.com/products/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define TCS_OUT 4
#define TCS_S0  2
#define TCS_S1  15
#define TCS_S2  18
#define TCS_S3  19

struct Cal {
  unsigned long r = 0;
  unsigned long g = 0;
  unsigned long b = 0;
  bool set = false;
};

Cal calBlack, calWhite;

void setScaling20Percent() {
  digitalWrite(TCS_S0, HIGH);
  digitalWrite(TCS_S1, LOW);
}

unsigned long readPulseWidth(bool s2, bool s3) {
  digitalWrite(TCS_S2, s2 ? HIGH : LOW);
  digitalWrite(TCS_S3, s3 ? HIGH : LOW);
  delay(3);
  return pulseIn(TCS_OUT, LOW, 25000);
}

void readRaw(unsigned long &r, unsigned long &g, unsigned long &b) {
  r = readPulseWidth(false, false);
  b = readPulseWidth(false, true);
  g = readPulseWidth(true, true);
}

int clamp255(int x) {
  if (x < 0) return 0;
  if (x > 255) return 255;
  return x;
}

int normalize(unsigned long raw, unsigned long blackRaw, unsigned long whiteRaw) {
  if (blackRaw == 0 || whiteRaw == 0) return 0;

  unsigned long rawMin = min(blackRaw, whiteRaw);
  unsigned long rawMax = max(blackRaw, whiteRaw);

  if (raw < rawMin) raw = rawMin;
  if (raw > rawMax) raw = rawMax;

  long val = (long)(rawMax - raw) * 255L / (long)(rawMax - rawMin);
  return clamp255((int)val);
}

const char* detectColor(int R, int G, int B) {
  int maxv = max(R, max(G, B));
  int minv = min(R, min(G, B));

  if (maxv < 40) return "BLACK";
  if (minv > 180 && (maxv - minv) < 40) return "WHITE";

  if (R > G + 30 && R > B + 30) return "RED";
  if (G > R + 30 && G > B + 30) return "GREEN";
  if (B > R + 30 && B > G + 30) return "BLUE";

  if (R > 160 && G > 160 && B < 100) return "YELLOW";
  if (G > 160 && B > 160 && R < 100) return "CYAN";
  if (R > 160 && B > 160 && G < 100) return "MAGENTA";

  return "UNKNOWN";
}

void printCalStatus() {
  Serial.print("Black cal: ");
  Serial.print(calBlack.set ? "SET" : "NOT SET");
  Serial.print(" | White cal: ");
  Serial.println(calWhite.set ? "SET" : "NOT SET");
}

void setup() {
  Serial.begin(115200);

  pinMode(TCS_S0, OUTPUT);
  pinMode(TCS_S1, OUTPUT);
  pinMode(TCS_S2, OUTPUT);
  pinMode(TCS_S3, OUTPUT);
  pinMode(TCS_OUT, INPUT);

  setScaling20Percent();

  Serial.println("TCS3200 + ESP32 color demo");
  Serial.println("1) Put sensor on BLACK, press 'b' in Serial Monitor");
  Serial.println("2) Put sensor on WHITE paper, press 'w'");
  Serial.println("Then it prints RGB (0-255) + color name");
  printCalStatus();
}

void loop() {
  if (Serial.available()) {
    char c = (char)Serial.read();
    if (c == 'b' || c == 'B') {
      readRaw(calBlack.r, calBlack.g, calBlack.b);
      calBlack.set = true;
      Serial.print("Saved BLACK raw: R="); Serial.print(calBlack.r);
      Serial.print(" G="); Serial.print(calBlack.g);
      Serial.print(" B="); Serial.println(calBlack.b);
      printCalStatus();
    } else if (c == 'w' || c == 'W') {
      readRaw(calWhite.r, calWhite.g, calWhite.b);
      calWhite.set = true;
      Serial.print("Saved WHITE raw: R="); Serial.print(calWhite.r);
      Serial.print(" G="); Serial.print(calWhite.g);
      Serial.print(" B="); Serial.println(calWhite.b);
      printCalStatus();
    }
  }

  unsigned long rr, gg, bb;
  readRaw(rr, gg, bb);

  if (!calBlack.set || !calWhite.set) {
    Serial.print("RAW  R: "); Serial.print(rr);
    Serial.print("  G: "); Serial.print(gg);
    Serial.print("  B: "); Serial.print(bb);
    Serial.println("  | press 'b' for black, 'w' for white");
    delay(200);
    return;
  }

  int R = normalize(rr, calBlack.r, calWhite.r);
  int G = normalize(gg, calBlack.g, calWhite.g);
  int B = normalize(bb, calBlack.b, calWhite.b);

  const char* name = detectColor(R, G, B);

  Serial.print("RGB  R: "); Serial.print(R);
  Serial.print("  G: "); Serial.print(G);
  Serial.print("  B: "); Serial.print(B);
  Serial.print("  -> ");
  Serial.println(name);

  delay(200);
}
