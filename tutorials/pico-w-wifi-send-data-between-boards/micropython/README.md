# Micropython examples

- [`pico_w_server.py`](./pico_w_server.py) — MicroPython server for a Pico W: connects to Wi‑Fi, opens a TCP socket on port 80, and sends a random integer to each connecting client.
- [`pico_w_client.py`](./pico_w_client.py) — MicroPython client for a Pico W: connects to Wi‑Fi, connects to the server IP on port 80, sends a simple request, receives and prints the server's reply (replace the placeholder with the server's address).

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/pico-w-wifi-send-data-between-boards)  
Parts used: [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
