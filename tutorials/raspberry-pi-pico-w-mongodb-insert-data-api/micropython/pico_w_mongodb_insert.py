# Connects the Raspberry Pi Pico W to Wi‑Fi and sends an insertOne request to the MongoDB Atlas Data API with a JSON document payload.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mongodb-insert-data-api
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import machine
import urequests as requests
import network
import time

import constants


def connect_to_wifi(ssid, psk):
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, psk)

    while not wlan.isconnected() and wlan.status() >= 0:
        print("Waiting to Connect")
        time.sleep(10)
    if not wlan.isconnected():
        raise Exception("Wifi not available")
    print("Connected to WiFi")


try:
    connect_to_wifi(constants.INTERNET_NAME, constants.INTERNET_PASSWORD)
    # Need to substitute from DATA API
    url = "<url>/action/insertOne"
    headers = { "api-key": "<api key>" }

    documentToAdd = {"device": "MyPico", "readings": [77, 80, 40, 60, 70, 80, 10]}

    insertPayload = {
        "dataSource": "Cluster0",
        "database": "WeatherData2",
        "collection": "BME2802",
        "document": documentToAdd,
    }

    print("sending...")

    response = requests.post(url, headers=headers, json=insertPayload)

    print("Response: (" + str(response.status_code) + "), msg = " + str(response.text))

    if response.status_code == 201:
        print("Added Successfully")
    else:
        print("Error")

    # Always close response objects so we don't leak memory
    response.close()

except Exception as e:
    print(e)
