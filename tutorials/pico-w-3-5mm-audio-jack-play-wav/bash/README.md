# Bash examples

- [`convert_wav.sh`](./convert_wav.sh) — Install ffmpeg (macOS) and convert an input WAV to 8-bit mono PCM at 8000 Hz suitable for the Pico playback code.
- [`upload_wav.sh`](./upload_wav.sh) — Install mpremote, locate the Pico serial device, set the PORT variable, and copy the prepared WAV file to the Pico filesystem.
- [`deploy_and_run.sh`](./deploy_and_run.sh) — Copy the play_wav.py script to the Pico and run it over the serial connection using mpremote.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/pico-w-3-5mm-audio-jack-play-wav)  
Parts used: [Pre-Soldered 3.5mm Stereo Audio Jack Breakout Board for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board) · [400-Point Small Solderless Breadboard for Arduino, Raspberry Pi & ESP32](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
