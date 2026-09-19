// Runs a Wi-Fi web server on an ESP32 that serves an HTML page with sliders and handles requests to update LED PWM brightness and a servo angle.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-servo-web-sliders-led-control
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
//             https://shillehtek.com/products/shillehtek-universal-power-supply-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* SSID = "YourNetwork";
const char* PASS = "YourPassword";
const int LED = 2, SERVO_PIN = 13;

WebServer server(80);
Servo servo;
int ledVal = 0, servoVal = 90;

const char PAGE[] PROGMEM = R"HTML(
<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width,initial-scale=1'>
<style>body{font-family:sans-serif;text-align:center;padding:20px}
input{width:90%;height:40px}h2{margin:30px 0 5px}</style></head><body>
<h1>ESP32 Sliders</h1>
<h2>LED brightness: <span id='lv'>0</span></h2>
<input type='range' min='0' max='255' value='0' oninput='send("led",this.value,"lv")'>
<h2>Servo angle: <span id='sv'>90</span>°</h2>
<input type='range' min='0' max='180' value='90' oninput='send("servo",this.value,"sv")'>
<script>
function send(k,v,id){document.getElementById(id).textContent=v;fetch('/set?'+k+'='+v);}
</script></body></html>)HTML";

void handleSet() {
  if (server.hasArg("led"))   { ledVal   = server.arg("led").toInt();   analogWrite(LED, ledVal); }
  if (server.hasArg("servo")) { servoVal = server.arg("servo").toInt(); servo.write(servoVal); }
  server.send(200, "text/plain", "ok");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  servo.attach(SERVO_PIN, 500, 2400);          // pulse range for most hobby servos
  servo.write(servoVal);

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
  Serial.println("Open http://" + WiFi.localIP().toString());

  server.on("/",    []() { server.send_P(200, "text/html", PAGE); });
  server.on("/set", handleSet);
  server.begin();
}

void loop() { server.handleClient(); }
