// ESP32 Arduino sketch that reads a KY-018 photoresistor and DHT11 sensor, hosts a single-page web dashboard from flash, and streams sensor values over a WebSocket while handling LED toggle commands.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-websocket-dashboard-live-sensor-chart
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
//             https://shillehtek.com/products/shillehtek-dht11-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const int LDR_PIN = 34, LED_PIN = 2;
DHT dht(4, DHT11);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// The whole web page lives in flash. No external files, no CDN.
const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta name="viewport" content="width=device-width,initial-scale=1">
<title>ESP32 Live</title>
<style>body{font-family:sans-serif;background:#111;color:#eee;text-align:center;margin:0;padding:16px}
.v{font-size:2em;margin:0 8px}canvas{width:100%;max-width:640px;background:#222;border-radius:8px}
button{font-size:1.1em;padding:10px 24px;border:0;border-radius:6px;background:#2a7;color:#fff}</style></head>
<body><h2>ESP32 Live Dashboard</h2>
<div>Light <span class="v" id="L">--</span> Temp <span class="v" id="T">--</span>C  Hum <span class="v" id="H">--</span>%</div>
<canvas id="c" width="640" height="200"></canvas>
<button onclick="ws.send('toggle')">Toggle LED</button>
<script>
const c=document.getElementById('c'),g=c.getContext('2d'),hist=[];
const ws=new WebSocket('ws://'+location.host+'/ws');
ws.onmessage=e=>{const d=JSON.parse(e.data);
  document.getElementById('L').textContent=d.light;
  document.getElementById('T').textContent=d.temp.toFixed(1);
  document.getElementById('H').textContent=d.hum.toFixed(0);
  hist.push(d.light); if(hist.length>128) hist.shift(); draw();};
function draw(){g.clearRect(0,0,640,200);g.strokeStyle='#2a7';g.lineWidth=2;g.beginPath();
  hist.forEach((v,i)=>{const x=i*5,y=195-v/4095*190; i?g.lineTo(x,y):g.moveTo(x,y);});g.stroke();}
</script></body></html>)rawliteral";

void onWsEvent(AsyncWebSocket* s, AsyncWebSocketClient* client, AwsEventType type,
               void* arg, uint8_t* data, size_t len) {
  if (type == WS_EVT_CONNECT) Serial.printf("client %u connected\n", client->id());
  if (type == WS_EVT_DATA) {                                  // a message from the browser
    String msg; for (size_t i = 0; i < len; i++) msg += (char)data[i];
    if (msg == "toggle") digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); dht.begin();
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  Serial.println("Open http://" + WiFi.localIP().toString());
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* r) { r->send(200, "text/html", PAGE); });
  server.begin();
}

void loop() {
  static unsigned long last = 0; static int tick = 0; static float t = 0, h = 0;
  if (millis() - last >= 500) {                               // push twice a second
    last = millis();
    if (++tick % 4 == 0) {                                    // DHT11 only every 2 s
      float nt = dht.readTemperature(), nh = dht.readHumidity();
      if (!isnan(nt)) { t = nt; h = nh; }
    }
    int light = analogRead(LDR_PIN);                          // 0..4095
    String json = "{\"light\":" + String(light) + ",\"temp\":" + String(t, 1) + ",\"hum\":" + String(h, 0) + "}";
    ws.textAll(json);                                         // to every connected browser
    ws.cleanupClients();
  }
}
