# Initializes UART to read NMEA sentences from the GPS, provides a Wi‑Fi connection helper, and performs HTTP requests for reverse geocoding (MicroPython code for Pico W).
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-neo-6m-gps-reverse-geolocator
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
#             https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

"""
NMEA (National Marine Electronics Association) is a standard for formatting data from GPS and other navigation devices.
NMEA sentences are ASCII text lines that provide specific types of navigation data. Common NMEA sentence types:
- GPGGA: Global Positioning System Fix Data, provides time, position, and fix-related data.
- GPGSA: GPS DOP and Active Satellites, gives satellite fix information and dilution of precision.
- GPGLL: Geographic Position, Latitude/Longitude, provides position data.
- GPRMC: Recommended Minimum Specific GNSS Data, gives time, date, position, and speed data.
- GPVTG: Track Made Good and Ground Speed, provides course and speed data.
"""

import machine
import time
import urequests
import network
import config

# Initialize UART for GPS communication
uart = machine.UART(0, baudrate=9600, tx=machine.Pin(0), rx=machine.Pin(1))

def connect_internet(name, password):
    try:
        sta_if = network.WLAN(network.STA_IF)
        sta_if.active(True)
        sta_if.connect(name, password)

        for i in range(0, 10):
            if not sta_if.isconnected():
                time.sleep(1)
        print("Connected to Wi-Fi")
    except Exception as e:
        print('There was an issue connecting to WIFI')
        print(e)

def reverse_geocode(latitude, longitude):
    """
    Convert latitude and longitude to a human-readable address using OpenCage API.
    """
    api_key = "Put your key here"  # Your provided API key
    # Manually construct the URL with query parameters
    full_url = f"https://api.opencagedata.com/geocode/v1/json?q={latitude}+{longitude}&key={api_key}"

    # Validate coordinates
    if not (-90 <= latitude <= 90) or not (-180 <= longitude <= 180):
        print("Invalid GPS coordinates.")
        return "Unknown", "Unknown"

    try:
        print(f"Requesting URL: {full_url}")  # Debugging log
        response = urequests.get(full_url, timeout=5)

        # Check if the request was successful
        if response.status_code == 200:
            data = response.json()

            if data.get('results'):
                components = data['results'][0].get('components', {})
                city = components.get('city') or components.get('town') or components.get('village') or "Unknown"
                country = components.get('country', "Unknown")
                return city, country
            else:
                print("No results found in API response.")
                return "Unknown", "Unknown"
        elif response.status_code == 403:
            print("Error: API key is invalid or blocked.")
            return "Unknown", "Unknown"
        elif response.status_code == 429:
            print("Error: Rate limit exceeded. Try again later.")
            return "Unknown", "Unknown"
        else:
            print(f"Unexpected API error: {response.status_code}, {response.text}")
            return "Unknown", "Unknown"
    except Exception as e:
        print(f"Error during API request: {e}")
        return "Unknown", "Unknown"


def validate_checksum(sentence):
    """
    Validates the checksum of an NMEA sentence.

    NMEA sentences include a checksum at the end, which is used to verify
    the integrity of the data. This function calculates the checksum by
    XORing all characters in the data portion of the sentence and compares
    it to the checksum provided in the sentence.

    Args:
        sentence (str): The NMEA sentence to validate, including the checksum.

    Returns:
        bool: True if the checksum is valid, False otherwise.
    """
    if '*' not in sentence:
        return False  # Invalid sentence format

    # Split the sentence into data and checksum parts
    data, checksum = sentence.split('*')

    if not checksum:
        return False

    # Calculate checksum by XORing all characters in the data part
    calculated_checksum = 0
    for char in data:
        calculated_checksum ^= ord(char)
    return calculated_checksum == int(checksum, 16)

def extract_coordinates(sentence):
    """
    Extract coordinates and altitude from GPGGA sentence.
    Returns a tuple: (latitude, longitude, altitude, city, country) or None if invalid.
    """
    # Split the sentence by commas
    print(sentence)
    parts = sentence.split(",")

    # Validate the sentence
    if parts[0] != "GPGGA":
        raise ValueError("Input is not a valid GPGGA sentence.")

    # Check GPS signal validity
    gps_quality = parts[6]
    if gps_quality != "1":
        return None

    # Extract latitude
    raw_lat = parts[2]
    lat_direction = parts[3]
    latitude = float(raw_lat[:2]) + float(raw_lat[2:]) / 60  # Convert to decimal degrees
    if lat_direction == "S":
        latitude = -latitude

    # Extract longitude
    raw_lon = parts[4]
    lon_direction = parts[5]
    longitude = float(raw_lon[:3]) + float(raw_lon[3:]) / 60  # Convert to decimal degrees
    if lon_direction == "W":
        longitude = -longitude

    # Extract altitude
    altitude = float(parts[9])
    city, country = reverse_geocode(latitude, longitude)
    return latitude, longitude, altitude, city, country


def read_gps(read_coordinates_only=False):
    buffer = b""
    while True:
        if uart.any():  # Check if there's data available in UART buffer
            data = uart.read()  # Read the data from UART
            if data:
                buffer += data  # Append data to buffer

                # Process complete NMEA sentences
                while b'\r\n' in buffer:  # Look for sentence endings
                    raw_line, buffer = buffer.split(b'\r\n', 1)  # Split buffer at sentence boundary
                    line = raw_line.decode('utf-8')  # Decode from bytes to string
                    if line.startswith('$'):
                        lines = line.split('$')
                        for line in lines:
                            if line == '' or not validate_checksum(line):
                                continue

                            if read_coordinates_only:
                                if line.startswith('GPGGA'):
                                    coordinates = extract_coordinates(line)
                                    if coordinates:
                                        latitude, longitude, altitude, city, country = coordinates
                                        print(f"Latitude: {latitude}, Longitude: {longitude}, Altitude: {altitude} m, City: {city}, Country: {country}")
                                    else:
                                        print("GPS signal not available")
                            else:
                                print(line)  # Print the full NMEA sentence

        time.sleep(1)  # Add a small delay to prevent CPU overuse

try:
    print("Reading GPS data...")
    # Pass `True` to only print coordinates and altitude, or `False` for all data
    connect_internet('SMA', config.password)
    read_gps(read_coordinates_only=False)
except KeyboardInterrupt:
    print("Stopped")
