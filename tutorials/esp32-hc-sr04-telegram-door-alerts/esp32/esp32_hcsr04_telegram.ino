// ESP32 Arduino sketch that connects to Wi‑Fi, reads the HC‑SR04 ultrasonic sensor, and sends Telegram alerts when an object is within ~1 m for 3 seconds, with a 30 second cooldown.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-hc-sr04-telegram-door-alerts
// Parts used: https://shillehtek.com/products/shillehtek-400-point-breadboard
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WiFiClientSecure.h>

// --- Put your secrets here (keep these private) ---
// Replace the empty strings with your own Wi-Fi + Telegram credentials.
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
const char* TELEGRAM_BOT_TOKEN = "";
const char* TELEGRAM_CHAT_ID = "";

// --- Pins ---
const int ECHO_PIN = 19;
const int TRIG_PIN = 18;

// --- Behavior ---
const int THRESH_CM = 100;                 // 1 meter
const unsigned long HOLD_MS = 3000;        // 3 seconds
const unsigned long COOLDOWN_MS = 30000;   // 30 seconds

unsigned long closeStartMs = 0;
unsigned long lastAlertMs = 0;

String urlEncode(const String& s) {
  String out;
  const char *hex = "0123456789ABCDEF";
  for (size_t i = 0; i < s.length(); i++) {
    char c = s[i];
    if (isalnum((unsigned char)c) || c == '-' || c == '_' || c == '.' || c == '~') out += c;
    else if (c == ' ') out += "%20";
    else {
      out += '%';
      out += hex[(c >> 4) & 0xF];
      out += hex[c & 0xF];
    }
  }
  return out;
}

bool sendTelegram(const String& msg) {
  WiFiClientSecure client;
  client.setInsecure(); // demo: skip cert validation

  String url = "/bot" + String(TELEGRAM_BOT_TOKEN)
             + "/sendMessage?chat_id=" + String(TELEGRAM_CHAT_ID)
             + "&text=" + urlEncode(msg);

  if (!client.connect("api.telegram.org", 443)) {
    Serial.println("Telegram connect failed");
    return false;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n"
             + "Host: api.telegram.org\r\n"
             + "Connection: close\r\n\r\n");

  while (client.connected() || client.available()) {
    String line = client.readStringUntil('\n');
    if (line.indexOf("\"ok\":true") >= 0) return true;
  }
  return false;
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;

  return (duration * 0.0343f) / 2.0f;
}

float readDistanceCmFiltered() {
  float a = readDistanceCm();
  delay(30);
  float b = readDistanceCm();
  delay(30);
  float c = readDistanceCm();

  if (a > b) { float t=a; a=b; b=t; }
  if (b > c) { float t=b; b=c; c=t; }
  if (a > b) { float t=a; a=b; b=t; }
  return b;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  btStop();
  WiFi.setTxPower(WIFI_POWER_11dBm);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  sendTelegram("✅ Your device is online");
}

void loop() {
  unsigned long now = millis();
  float cm = readDistanceCmFiltered();

  if (cm > 0) {
    bool isClose = (cm <= THRESH_CM);

    if (isClose) {
      if (closeStartMs == 0) closeStartMs = now;

      bool heldLongEnough = (now - closeStartMs) >= HOLD_MS;
      bool cooldownOver = (now - lastAlertMs) >= COOLDOWN_MS;

      if (heldLongEnough && cooldownOver) {
        String msg = "🚪 Someone is near the door: " + String(cm, 1) + " cm";
        bool ok = sendTelegram(msg);
        Serial.println(ok ? "Alert sent" : "Alert failed");

        lastAlertMs = now;
        closeStartMs = 0;
      }
    } else {
      closeStartMs = 0;
    }
  } else {
    closeStartMs = 0;
  }

  delay(120);
}
