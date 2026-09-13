// ESP32 web server sketch that hosts a simple HTML dashboard and an endpoint (/readMoisture) to return the current moisture percentage to the page's JavaScript.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-soil-moisture-sensor-wifi-dashboard-readout
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

int moisturePercent;
int sensorAnalog;

// Change this to the ADC pin you are using
const int sensorPin = 34;

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char html_page[] PROGMEM = R"rawliteral(



  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Soil Moisture</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; padding: 30px; }
    h1 { font-size: 28px; }
    p { font-size: 32px; }
  </style>


  <h1>Soil Moisture With ESP32</h1>
  <p>Moisture Level: <span id="MoistureVal">0</span>%</p>

  <script>
    setInterval(function() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("MoistureVal").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/readMoisture", true);
      xhttp.send();
    }, 500);
  </script>


)rawliteral";

void MainPage() {
  server.send(200, "text/html", html_page);
}

void SoilMoisture() {
  String moistureValue = String(moisturePercent);
  server.send(200, "text/plain", moistureValue);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println();
  Serial.print("Connected. Local IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", MainPage);
  server.on("/readMoisture", SoilMoisture);
  server.begin();
}

void loop() {
  sensorAnalog = analogRead(sensorPin);
  moisturePercent = 100 - ((sensorAnalog / 4095.00) * 100);

  server.handleClient();

  Serial.print("Moisture = ");
  Serial.print(moisturePercent);
  Serial.println("%");

  delay(1000);
}
