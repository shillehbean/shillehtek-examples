# MicroPython example for a Pico that sends raw DFPlayer UART frames, sets volume and plays a track, and uses the BUSY pin to wait until playback finishes before starting the next track.
#
# Buy this module: https://shillehtek.com/products/mp3-player-module-tf-card-arduino-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mp3-player-module-tf-card-arduino-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MP3-TF-16P - Pico MicroPython Example (raw frames + BUSY pin)
# TX->GP1, RX(via 1k)->GP0, BUSY->GP2

from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
busy = Pin(2, Pin.IN, Pin.PULL_UP)     # LOW while playing

def cmd(command, param=0):
    hi, lo = (param >> 8) & 0xFF, param & 0xFF
    frame = [0x7E, 0xFF, 0x06, command, 0x00, hi, lo]
    checksum = -sum(frame[1:]) & 0xFFFF
    frame += [(checksum >> 8) & 0xFF, checksum & 0xFF, 0xEF]
    uart.write(bytes(frame))
    time.sleep_ms(200)

cmd(0x3F)              # init
time.sleep(1)
cmd(0x06, 18)          # volume
cmd(0x03, 1)           # play 0001.mp3
print("Playing...")

while busy.value() == 0:      # wait until the track finishes
    time.sleep_ms(100)
print("Track finished - playing track 2")
cmd(0x03, 2)
