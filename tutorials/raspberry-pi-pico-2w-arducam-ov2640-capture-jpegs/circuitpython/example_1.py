# Main CircuitPython script to control the ArduCAM OV2640, set JPEG resolution, toggle the onboard LED, and save captured JPEG data into /images on the Pico filesystem.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-2w-arducam-ov2640-capture-jpegs
# Parts used: https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# code.py - ArduCAM capture -> /images on CIRCUITPY
import time as utime
import board, digitalio, os
from Arducam import *

ONCE = 512
RESOLUTION = 0x04
DIR_PATH = "/images"

buf = bytearray(ONCE)

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT
led.value = False

def log(msg):
    print("[{:.3f}] {}".format(utime.monotonic(), msg))

def set_resolution(cam, value):
    if   value == 0x00: cam.OV2640_set_JPEG_size(OV2640_160x120)
    elif value == 0x01: cam.OV2640_set_JPEG_size(OV2640_176x144)
    elif value == 0x02: cam.OV2640_set_JPEG_size(OV2640_320x240)
    elif value == 0x03: cam.OV2640_set_JPEG_size(OV2640_352x288)
    elif value == 0x04: cam.OV2640_set_JPEG_size(OV2640_640x480)
    elif value == 0x05: cam.OV2640_set_JPEG_size(OV2640_800x600)
    elif value == 0x06: cam.OV2640_set_JPEG_size(OV2640_1024x768)
    elif value == 0x07: cam.OV2640_set_JPEG_size(OV2640_1280x1024)
    elif value == 0x08: cam.OV2640_set_JPEG_size(OV2640_1600x1200)
    else:               cam.OV2640_set_JPEG_size(OV2640_640x480)

def ensure_dir(path):
    try:
        os.listdir(path)
    except OSError:
        try:
            os.mkdir(path)
        except Exception as e:
            log("Failed to create {}: {}".format(path, e))

def unique_name():
    t = int(utime.monotonic())
    return "{}/image_{:010d}.jpg".format(DIR_PATH, t)

def save_fifo_to_file(cam, length, path):
    log("Saving {} bytes to {}".format(length, path))
    led.value = True
    with open(path, "wb") as f:
        cam.SPI_CS_LOW()
        cam.set_fifo_burst()
        sent = 0
        try:
            while sent < length:
                n = ONCE if (length - sent) >= ONCE else (length - sent)
                cam.spi.readinto(buf, start=0, end=n)  # <-- fixed signature
                f.write(memoryview(buf)[:n])
                sent += n
        finally:
            cam.SPI_CS_HIGH()
            cam.clear_fifo_flag()
    led.value = False
    log("Saved {}".format(path))

def capture_one(cam):
    cam.flush_fifo()
    cam.clear_fifo_flag()
    cam.start_capture()
    t0 = utime.monotonic()
    while cam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK) == 0:
        if utime.monotonic() - t0 > 5.0:
            raise RuntimeError("Timeout waiting for CAP_DONE")
        utime.sleep(0.005)
    length = cam.read_fifo_length()
    if length == 0 or length > 8_000_000:
        raise RuntimeError("Bad FIFO length: {}".format(length))
    save_fifo_to_file(cam, length, unique_name())

def main():
    ensure_dir(DIR_PATH)
    log("Init camera")
    cam = ArducamClass(OV2640)
    cam.Camera_Init()
    set_resolution(cam, RESOLUTION)
    utime.sleep(0.3)
    capture_one(cam)
    log("Done.")

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        led.value = False
        log("ERROR: {}".format(e))
        while True:
            log("HB: error state")
            utime.sleep(2)
