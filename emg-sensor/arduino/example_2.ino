// Perform a moving-average smoothing over N analog samples from A0 to stabilize the EMG signal and detect flexes more reliably than single-sample thresholding.
//
// Buy this module: https://shillehtek.com/products/emg-muscle-signal-sensor-module-kit-for-arduino-robotics
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/emg-muscle-signal-sensor-module-kit-for-arduino-robotics-manual
// More examples: https://github.com/shillehtek/examples
//

// ShillehTek EMG Sensor - Smoothed reading with a moving average.
// Averaging over N samples makes flex detection much more reliable.

const int EMG_PIN = A0;
const int N = 16;               // window size
int buf[N];
int idx = 0;
long sum = 0;

const int FLEX_THRESHOLD = 380;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < N; i++) buf[i] = 0;
}

void loop() {
  int raw = analogRead(EMG_PIN);
  sum -= buf[idx];
  buf[idx] = raw;
  sum += raw;
  idx = (idx + 1) % N;
  int avg = sum / N;

  Serial.print("raw:");
  Serial.print(raw);
  Serial.print("  avg:");
  Serial.print(avg);
  Serial.println(avg > FLEX_THRESHOLD ? "  FLEX!" : "");

  delay(20);
}
