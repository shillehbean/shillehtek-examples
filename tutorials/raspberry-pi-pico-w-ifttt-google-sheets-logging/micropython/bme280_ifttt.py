# Connects the Pico W to Wi‑Fi, reads temperature/pressure/humidity from a BME280 over I2C, and sends the values to an IFTTT webhook via HTTPS POST.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-ifttt-google-sheets-logging
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import urequests
import time
import machine
import network
from machine import Pin, I2C
import bme280

import config


SSID = config.SSID
WIFI_PASSWORD = config.WIFI_PASSWORD

EVENT_NAME = 'BME280_YT'
IFTTT_KEY = 'czLk7ytVFFpRQZuAeEOeiXi7h18XaGANp3oi1oy_MNm'
IFTTT_URL = f'/trigger/{EVENT_NAME}/with/key/{IFTTT_KEY}'
server = 'maker.ifttt.com'

i2c = I2C(0, sda=Pin(20), scl=Pin(21), freq=400000)
bme = bme280.BME280(i2c=i2c)


def connect_wifi():
  try:
    sta_if = network.WLAN(network.STA_IF)
    sta_if.active(True)
    sta_if.connect(SSID, WIFI_PASSWORD)

    for i in range(0, 10):
      if not sta_if.isconnected():
        time.sleep(1)
    print("Connected to Wi-Fi")
  except Exception as e:
    print('There was an issue connecting to WIFI')
    print(e)


def make_ifttt_request():
    json_data = '{"value1":"' + bme.values[0] + '","value2":"' + bme.values[1]  + \
        '","value3":"' + bme.values[2] + '"}'
    headers = {'Content-Type': 'application/json'}
    response = urequests.post('https://' + server + IFTTT_URL, data=json_data, headers=headers)
    print('Response:', response.content.decode())
    response.close()
    print('Closing Connection')


connect_wifi()
counter = 0
while True:
    counter += 1
    time.sleep(1)
    print(f'Uploading Value: {str(counter)}')
    make_ifttt_request()
