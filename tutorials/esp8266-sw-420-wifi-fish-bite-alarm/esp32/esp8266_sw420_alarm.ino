// ESP8266/ESP32 Arduino-framework sketch that runs a simple HTTP server, monitors an SW-420 vibration sensor with pulseIn, logs events, and toggles an alarm/LED via /start/1 and /stop/0 HTTP endpoints.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp8266-sw-420-wifi-fish-bite-alarm
// Parts used: https://shillehtek.com/products/vibration-sensor-sw-420-arduino-module
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/nodemcu-esp8266-development-board-with-0-96-inch-oled-display-type-c-with-soldering-and-foam
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define vibsensorPin 5
#define ledPin 13
#include <ESP8266WiFi.h>

const char* ssid = "Redmi";
const char* password = "";
boolean bite = false;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  pinMode(vibsensorPin, INPUT);
  digitalWrite(ledPin, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  long fishAlarm = pulseIn(vibsensorPin, HIGH);
  if (fishAlarm > 100) {
    bite = true;
    Serial.println(fishAlarm);
    Serial.println(bite);
  }

  WiFiClient client = server.available();
  if (!client) { return; }

  while (!client.available()) { delay(1); }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  int val;
  if (req.indexOf("/stop/0") != -1)
    val = 0;
  else if (req.indexOf("/start/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  digitalWrite(ledPin, val);
  client.flush();

  String s = "HTTP/1.1 200 OK\r\n Content-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  if (bite == true) {
    s += "!!!BITE!!!";
    bite = false;
  } else {
    s += "no bite";
  }

  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
}
