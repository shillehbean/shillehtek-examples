# Runs on the Pico to read characters from stdin, accumulate them until a comma is seen, and append each completed value as a new line to data.csv.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-serial-save-pc-data-csv
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
from sys import stdin
import uselect

csv_filename = "data.csv"

def save_to_csv(data):
  with open(csv_filename, "a") as f:
    f.write(data + "\n")

while True:
  select_result = uselect.select([stdin], [], [], 0)
  buffer = ''

  while select_result[0]:
    input_character = stdin.read(1)

    if input_character != ',':
        buffer += input_character
    else:
        save_to_csv(buffer)
        buffer = ''

    select_result = uselect.select([stdin], [], [], 0)
