# MicroPython script for the Raspberry Pi Pico W that initializes I2C for an MPU6050, reads certificate files, connects to Wi‑Fi, and prepares an MQTT client to publish sensor data to AWS IoT Core.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mpu6050-send-data-dynamodb
# Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
#             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import json
import machine
import network
import ssl
import time
import ubinascii

from simple import MQTTClient
from imu import MPU6050
from machine import Pin, I2C
import config

SSID = config.SSID
WIFI_PASSWORD = config.WIFI_PASSWORD
MQTT_CLIENT_ID = ubinascii.hexlify(machine.unique_id())
MQTT_CLIENT_KEY = "6912b69415aa106cb16c0d8008df840cd4e584f0a273cb66eb98e3941108eb98-private.pem.key"
MQTT_CLIENT_CERT = "6912b69415aa106cb16c0d8008df840cd4e584f0a273cb66eb98e3941108eb98-certificate.pem.crt"
MQTT_BROKER = config.IOT_CORE_ENDPOINT
MQTT_BROKER_CA = "AmazonRootCA1.pem"

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
imu = MPU6050(i2c)

def read_pem(file):
    with open(file, "r") as input:
        text = input.read().strip()
    split_text = text.split("\n")
    base64_text = "".join(split_text[1:-1])
    return ubinascii.a2b_base64(base64_text)

def connect_internet():
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

def publish_mpu_values(x):
    ax = round(imu.accel.x, 2)
    payload = {
        "point_number": x,
        "value": str(ax),
        "topic": 'MPU6050/ax'
    }
    mqtt_client.publish('MPU6050/ax', json.dumps(payload))

connect_internet()

key = read_pem(MQTT_CLIENT_KEY)
cert = read_pem(MQTT_CLIENT_CERT)
ca = read_pem(MQTT_BROKER_CA)

mqtt_client = MQTTClient(
    MQTT_CLIENT_ID,
    MQTT_BROKER,
    keepalive=60,
    ssl=True,
    ssl_params={
        "key": key,
        "cert": cert,
        "server_hostname": MQTT_BROKER,
        "cert_reqs": ssl.CERT_REQUIRED,
        "cadata": ca,
    },
)

print(f"Connecting to MQTT broker")
mqtt_client.connect()
print("Done Connecting, sending Values")

for i in range(1, 101):
    print("Publishing point ", i)
    publish_mpu_values(i)
