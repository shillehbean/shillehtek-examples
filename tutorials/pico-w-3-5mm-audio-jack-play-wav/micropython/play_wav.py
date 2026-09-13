# MicroPython script for Raspberry Pi Pico that reads a PCM unsigned 8-bit mono 8 kHz WAV file from the filesystem and plays it out via PWM on a configured GPIO pin.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-3-5mm-audio-jack-play-wav
# Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
import time

AUDIO_PIN = 15
SR = 8000

pwm = PWM(Pin(AUDIO_PIN))
pwm.freq(62500)

def play_wav_u8_mono(path="kart.wav", sr=SR, vol=0.20):
    with open(path, "rb") as f:
        hdr = f.read(44)
        if hdr[0:4] != b"RIFF" or hdr[8:12] != b"WAVE":
            raise ValueError("Not WAV")
        fmt = int.from_bytes(hdr[20:22], "little")
        ch = int.from_bytes(hdr[22:24], "little")
        rate = int.from_bytes(hdr[24:28], "little")
        bits = int.from_bytes(hdr[34:36], "little")
        if fmt != 1 or ch != 1 or bits != 8 or rate != sr:
            raise ValueError("Need PCM mono 8-bit 8000Hz")

        us = int(1_000_000 / sr)
        while True:
            chunk = f.read(512)
            if not chunk:
                break
            for b in chunk:
                x = (b - 128) / 128.0
                duty = int((0.5 + 0.5 * vol * x) * 65535)
                pwm.duty_u16(duty)
                time.sleep_us(us)

    pwm.duty_u16(0)

try:
    # Lower this if your speaker is loud
    play_wav_u8_mono("kart.wav", vol=0.18)
finally:
    # Kill PWM so there's no idle hiss/static
    try:
        pwm.duty_u16(0)
    except:
        pass
    pwm.deinit()

    # Force the pin low after PWM releases it (prevents floating noise)
    Pin(AUDIO_PIN, Pin.OUT).value(0)
