# MicroPython script for Raspberry Pi Pico W that connects to Wi‑Fi, reads BME280 sensor values, and sends JSON telemetry to Azure IoT Hub using an HTTP POST with a SAS token.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-bme280-azure-iot-pipeline
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import network
import time
import urequests
import json
from machine import Pin, I2C
import bme280

WIFI_SSID = 'SMA'
WIFI_PASS = 'mmmyellow'

IOTHUB_NAME = 'mypicowhub'
DEVICE_ID = 'picow1'
HEADERS = {
    'Authorization': 'SharedAccessSignature sr=mypicowhub.azure-devices.net%2Fdevices%2Fpicow1&sig=YOUR_SIG_HERE',
    'Content-Type': 'application/json'
}
URL = f'https://{IOTHUB_NAME}.azure-devices.net/devices/{DEVICE_ID}/messages/events?api-version=2020-09-30'

def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(WIFI_SSID, WIFI_PASS)
    while not wlan.isconnected():
        print("Connecting...")
        time.sleep(1)
    print("WiFi connected:", wlan.ifconfig())

def get_iso_timestamp():
    t = time.localtime()
    return "{}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}Z".format(t[0], t[1], t[2], t[3], t[4], t[5])

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
bme = bme280.BME280(i2c=i2c)

def send_to_azure():
    temp, pressure, humidity = bme.read_compensated_data()
    temp = round(temp / 100, 2)
    pressure = round(pressure / 25600, 2)
    humidity = round(humidity / 1024, 2)

    payload = {
        'deviceId': DEVICE_ID,
        'temperature': temp,
        'humidity': humidity,
        'pressure': pressure,
        'timestamp': get_iso_timestamp()
    }

    print("Sending:", payload)
    try:
        res = urequests.post(URL, headers=HEADERS, json=payload)
        print("Response:", res.status_code)
        res.close()
    except Exception as e:
        print("Error:", e)

connect_wifi()
while True:
    send_to_azure()
    time.sleep(1)
