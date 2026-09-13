# Initialize the Picamera2, capture frames repeatedly for a timed timelapse session, overlay the current time on each frame, and prepare an output directory for frames.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-4b-camera-module-build-timelapse
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import cv2
from datetime import datetime
import time
import os
from picamera2 import Picamera2

# Initialize the camera
camera = Picamera2()
camera.configure(camera.create_preview_configuration(main={"format": 'XRGB8888', "size": (1920, 1080)}))
camera.start()

# Timelapse settings
capture_interval = 10  # seconds between each frame
duration = 60 * 60 * 25  # duration of the timelapse capture in seconds (25 hours for this example)

# Create a new output directory with a timestamp
timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
output_dir = f"timelapse_frames_{timestamp}"
os.makedirs(output_dir, exist_ok=True)

start_time = time.time()

while time.time() - start_time < duration:
    frame = camera.capture_array()

    # Get the current time in hour:minute format
    current_time = datetime.now().strftime("%H:%M")

    # Define the position and font for the time overlay
    position = (frame.shape[1] - 200, 50)  # Adjust the position (x, y)
    font = cv2.FONT_HERSHEY_SIMPLEX
    font_scale = 1
    color = (0, 0, 0)  # Black color
    thickness = 3

    # Overlay the time on the frame
    cv2.putText(frame, current_time, position, font, font_scale, color, thickness, cv2.LINE_AA)

    # Save frame to disk
    filename = f"{output_dir}/frame_{int(time.time())}.jpg"
    cv2.imwrite(filename, frame)

    # Wait for the next capture
    time.sleep(capture_interval)

camera.stop()
