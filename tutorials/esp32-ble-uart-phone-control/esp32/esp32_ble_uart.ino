// ESP32 Arduino sketch that sets up a BLE Nordic UART (NUS) server, defines RX/TX characteristics and callbacks, and begins BLE initialization; it defines an output and sensor pin and toggles the output based on BLE write commands.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-ble-uart-phone-control
// Parts used: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Nordic UART Service UUIDs (recognized by most BLE terminal apps)
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define RX_UUID      "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"   // phone -> board (write)
#define TX_UUID      "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"   // board -> phone (notify)

const int OUT = 2, SENSOR = 32;
BLECharacteristic* tx;
bool connected = false;

class ServerCB : public BLEServerCallbacks {
  void onConnect(BLEServer*)    { connected = true;  Serial.println("phone connected"); }
  void onDisconnect(BLEServer* s) { connected = false; s->startAdvertising(); }   // be findable again
};

class RxCB : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* c) {
    String msg = c->getValue().c_str();          // works on ESP32 core 2.x and 3.x
    msg.trim(); msg.toLowerCase();
    Serial.println("got: " + msg);
    if (msg == "on"  || msg == "a") digitalWrite(OUT, HIGH);
    if (msg == "off" || msg == "b") digitalWrite(OUT, LOW);
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(OUT, OUTPUT);

  BLEDevice::init("ShillehTek-ESP32");           // the name you'll see in the app
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new ServerCB());
  BLEService* svc = server->createService(SERVICE_UUID);

  tx = svc->createCharacteristic(TX_UUID, BLECharacteristic::PROPERTY_NOTIFY);
  tx->addDescriptor(new BLE2902());              // lets the phone subscribe to notifications

  BLECharacteristic* rx = svc->createCharacteristic(RX_UUID, BLECharacteristic::PROPERTY_WRITE);
  rx->setCallbacks(new RxCB());

  svc->start();
  server->getAdvertising()->addServiceUUID(SERVICE_UUID);
  server->startAdvertising();
  Serial.println("advertising...");
}

void loop() {
  if (connected) {
    char buf[24];
    snprintf(buf, sizeof buf, "sensor=%d\n", analogRead(SENSOR));
    tx->setValue(buf);
    tx->notify();                                // push to the phone
  }
  delay(1000);
}
