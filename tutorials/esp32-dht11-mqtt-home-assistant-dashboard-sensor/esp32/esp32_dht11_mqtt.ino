// ESP32 Arduino sketch that reads a DHT11 sensor, connects to Wi-Fi and MQTT, publishes temperature and humidity topics, and subscribes to a relay command topic to control a relay and publish its state.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-dht11-mqtt-home-assistant-dashboard-sensor
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* SSID     = "YourNetwork";
const char* PASS     = "YourPassword";
const char* MQTT_IP  = "192.168.1.50";        // Home Assistant's IP
const char* MQTT_USER = "mqttuser";
const char* MQTT_PW   = "mqttpassword";

const char* T_TEMP = "home/livingroom/temperature";
const char* T_HUM  = "home/livingroom/humidity";
const char* T_CMD  = "home/livingroom/relay/set";   // Home Assistant -> ESP32
const char* T_STATE = "home/livingroom/relay";      // ESP32 -> Home Assistant

const int RELAY = 2;                                // onboard LED for now, relay IN later
DHT dht(4, DHT11);
WiFiClient net;
PubSubClient mqtt(net);

void onMessage(char* topic, byte* payload, unsigned int len) {
  String msg; for (unsigned int i = 0; i < len; i++) msg += (char)payload[i];
  bool on = (msg == "ON");
  digitalWrite(RELAY, on);
  mqtt.publish(T_STATE, on ? "ON" : "OFF", true);   // retained: HA sees the state after restarts
}

void connectMqtt() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-livingroom", MQTT_USER, MQTT_PW)) {
      mqtt.subscribe(T_CMD);
      Serial.println("MQTT connected");
    } else { Serial.print("MQTT failed rc="); Serial.println(mqtt.state()); delay(2000); }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  dht.begin();
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  mqtt.setServer(MQTT_IP, 1883);
  mqtt.setCallback(onMessage);
}

unsigned long lastPub = 0;
void loop() {
  if (!mqtt.connected()) connectMqtt();
  mqtt.loop();                                      // keeps the connection alive, runs callbacks

  if (millis() - lastPub > 10000) {                 // publish every 10 s
    lastPub = millis();
    float t = dht.readTemperature(), h = dht.readHumidity();
    if (!isnan(t)) { mqtt.publish(T_TEMP, String(t, 1).c_str()); }
    if (!isnan(h)) { mqtt.publish(T_HUM,  String(h, 0).c_str()); }
    Serial.printf("published %.1f C, %.0f %%\n", t, h);
  }
}
